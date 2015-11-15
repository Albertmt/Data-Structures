// **************************************************************
// *		   
// *  quadtree.h
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#ifndef QUADTREE_H
#define QUADTREE_H

#include "png.h"

class Quadtree
{
	public:
		/**
		 * Produces an empty Quadtree object, 
		 * i.e. one which has no associated 
		 * QuadtreeNode objects, and in which
		 * root is NULL.
		 **/
		Quadtree();
		
		/**
		 * This constructor's purpose is to 
		 * build a Quadtree representing the
		 * upper-left d by d block of the source image. 
		 **/
		Quadtree(PNG const & source, int resolution);

		/**
		 * Simply sets this Quadtree to be
		 * a copy of the parameter.
		 **/
		Quadtree(Quadtree const & other);
		
		/**
		 * Destructor. Obviously frees the
		 * memory associated with this Quadtree.
		 **/
		~Quadtree();

		/**
		 * Assignment operator.
		 **/
		Quadtree const & operator= (Quadtree const &other);
		
		/**
		 * Deletes the current contents of this
		 * Quadtree object, then turns it into a
		 * Quadtree object representing the 
		 * upper-left d by d block of source.
		 **/
		void buildTree (PNG const &source, int resolution);

		/**
		 * Gets the RGBAPixel corresponding to the
		 * pixel at coordinates (x, y) in the bitmap
		 * image which the Quadtree represents.
		 **/
		RGBAPixel getPixel (int x, int y) const;

		/**
		 * Returns the underlying PNG object
		 * represented by the Quadtree. Important function :)
		 **/
		PNG decompress() const;
		
		/**
		 * Rotates the Quadtree object's underlying
		 * image clockwise by 90 degrees.
		 **/
		void clockwiseRotate ();

		/**
		 * Compresses the image this Quadtree represents.
		 **/
		void prune (int tolerance);

		/**
		 * Returns a count of the total number of
		 * leaves the Quadtree would have if it were
		 * pruned as in the prune function.
		 **/
		int pruneSize (int tolerance) const;

		/**
		 * Calculates and returns the minimum 
		 * tolerance necessary to guarantee that
		 * upon pruning the tree, no more than 
		 * numLeaves leaves remain in the Quadtree.
		**/
		int idealPrune (int numLeaves) const;
		
	private:

	// A simple class representing a single node of a Quadtree.
	// You may want to add to this class; in particular, it could probably
	// use a constructor or two...
	class QuadtreeNode
	{
		public:
			//silly constructor, sets everything to NULL
			QuadtreeNode();

			//copies the whole hierarchy
			QuadtreeNode(QuadtreeNode * const  & other);
			
			//most common ctor
			QuadtreeNode(int X, int Y, int d);

			//another ctor for a leaf
			QuadtreeNode(int X, int Y, int d, RGBAPixel pix);
		
		QuadtreeNode* nwChild;  // pointer to northwest child
		QuadtreeNode* neChild;  // pointer to northeast child
		QuadtreeNode* swChild;  // pointer to southwest child
		QuadtreeNode* seChild;  // pointer to southeast child

		
		RGBAPixel element;  // the pixel stored as this node's "data"

		/*coordinates of the QuadtreeNode */
		int x;
		int y;
		/*size of the region*/
		int size;
	};
	
	QuadtreeNode* root;    // pointer to root of quadtree

	int imageSize;
	
	//PNG image;	
	/************ HELPER FUNCTIONS ************/

	/**
	 * Clears up all the memory associated with
	 * the given QuadTree.
	 **/
	void clear(QuadtreeNode * & subRoot);

	/**
	 * Copies the content of the source
	 * into the given QuadTree.
	 **/
	void copy(const Quadtree & source);
	
	/**
	 * Helper function for buildTree().
	 * Makes a subQuadtree starting at source.  
	 **/
	void partition(PNG const & image, QuadtreeNode * &source, int d);

	/**
	 * Helper function for filling elements
	 * not only for leaves, but also for 
	 * all the internal nodes.
	 **/
	void fillElements(QuadtreeNode * & source);
	
	/**
	 * Helper function for clockwiseRotate().
	 * Rotates the subQuadtree starting at source.  
	 **/
	void rotateNode(QuadtreeNode * source);
	
	/**
	 * Helper function for prune(). 
	 * Returns the leaf at the coordinates.
	 **/
	Quadtree::QuadtreeNode * leaf(int X, int Y);
	
	/**
	 * Computes the difference between two nodes.
	 **/
	int nodeDiff(QuadtreeNode* cRoot, QuadtreeNode * child) const;

	/**
	 * Helper function, that checks if the subtree
	 * starting at source is prunable or not.
	 **/
	bool prunable(QuadtreeNode * source, QuadtreeNode * start, int tol) const;

	/**
	 * Helper function for prune.
	 **/
	void pruneNode(QuadtreeNode* source, int tolerance);
	
	/**
	 *
	 **/
	int pruneSize(QuadtreeNode * source, int tolerance) const;

	/**** Functions added for testing/grading                ****/
	/**** Do not remove this line or copy its contents here! ****/
	#include "quadtree_given.h"
};

#endif

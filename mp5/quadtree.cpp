// **************************************************************
// *		   
// *  quadtree.cpp
// *		   
// *  Quadtree class
// *		   
// *  CS 225 Spring 2008
// *		   
// **************************************************************

#include "quadtree.h"
#include <iostream>
using namespace std;
//Silly constructor, creates an 
Quadtree::QuadtreeNode::QuadtreeNode(){
	nwChild = neChild = swChild = seChild = NULL;
	size = 0;
}

Quadtree::QuadtreeNode::QuadtreeNode(QuadtreeNode * const & other){
	if(other->nwChild != NULL){
		nwChild = new QuadtreeNode(other->nwChild);
		neChild = new QuadtreeNode(other->neChild);
		swChild = new QuadtreeNode(other->swChild);
		seChild = new QuadtreeNode(other->seChild);
	}
	
	else
		nwChild = neChild = swChild = seChild = NULL;
	
	element = other->element;
//	x = other->x;
//	y = other->y;
	size = other->size;	
}

Quadtree::QuadtreeNode::QuadtreeNode(int X, int Y, int d):x(X),y(Y),size(d){
	nwChild = neChild = swChild = seChild = NULL;
}

Quadtree::QuadtreeNode::QuadtreeNode(int X, int Y, int d, RGBAPixel pix){
	QuadtreeNode(X, Y, d);
	element = pix;
	nwChild = neChild = swChild = seChild = NULL;
}

void Quadtree::clear(QuadtreeNode * & subRoot){
	if (subRoot == NULL)
		return;
	clear(subRoot->nwChild);
	clear(subRoot->neChild);
	clear(subRoot->swChild);
	clear(subRoot->seChild);
	delete subRoot;
	subRoot = NULL;
}

Quadtree::~Quadtree(){
	clear(root);
	imageSize = 0;
}

void Quadtree::copy(const Quadtree & source){
	if(source.root == NULL){
		root = NULL;
		imageSize = 0;
	}
	else{
		root = new QuadtreeNode(source.root);
		imageSize = source.imageSize;
	}
}

Quadtree::Quadtree():root(NULL), imageSize(0){}

Quadtree::Quadtree(Quadtree const & other){
	copy(other);
}

Quadtree::Quadtree(PNG const & source, int resolution){
	root = NULL;
	imageSize = 0;
	buildTree(source, resolution);
}

Quadtree const & Quadtree ::operator= (Quadtree const &other){
	if (this != &other){
		clear(root);
		imageSize = 0;
		copy(other);
	}
	return *this;
}

void Quadtree::buildTree (PNG const &image, int resolution){
	clear(root);
	imageSize = resolution;
	root = new QuadtreeNode(0,0,resolution);
	partition(image, root, resolution);
}

void Quadtree::partition(PNG const & image, QuadtreeNode * & source, int d){
	if (d == 1)
		source->element = *image(source->x, source->y);
	else{
		source->nwChild = new QuadtreeNode(source->x, source->y, d/2);
			partition(image, source->nwChild, d/2);
		source->neChild = new QuadtreeNode(source->x + d/2, source->y, d/2);
			partition(image, source->neChild, d/2);
		source->swChild = new QuadtreeNode(source->x, source->y + d/2, d/2);
			partition(image, source->swChild, d/2);
		source->seChild = new QuadtreeNode(source->x+ d/2, source->y + d/2, d/2);
			partition(image, source->seChild, d/2);
		fillElements(source);
	}
}

void Quadtree::fillElements(QuadtreeNode * & source){
	if(source->nwChild == NULL) return;
	fillElements(source -> nwChild);
	fillElements(source -> neChild);
	fillElements(source -> swChild);
	fillElements(source -> seChild);
	int r =((int)(source->nwChild->element.red) 
	      + (int)(source->neChild->element.red)
	      + (int)(source->swChild->element.red)
	      + (int)(source->seChild->element.red)	)/4;  
	int g =((int)(source->nwChild->element.green) 
	      + (int)(source->neChild->element.green)
	      + (int)(source->swChild->element.green)
	      + (int)(source->seChild->element.green)	)/4;  
	int b =((int)(source->nwChild->element.blue) 
	      + (int)(source->neChild->element.blue)
	      + (int)(source->swChild->element.blue)
	      + (int)(source->seChild->element.blue)	)/4;  
	source -> element = RGBAPixel(r,g,b);	
}

RGBAPixel Quadtree::getPixel (int x, int y) const{
	QuadtreeNode * curr = root;
	int xx = 0, yy = 0;
	int d = imageSize;
	if(x > imageSize or y > imageSize or x < 0 or y < 0 or imageSize == 0)
		return RGBAPixel();
	else{
		
		while(curr->nwChild != NULL){
			d/=2;
			if(x < xx + d and y < yy + d) {curr = curr->nwChild;}
			if(x < xx + d and y>= yy + d) {curr = curr->swChild;yy+=d;}
			if(x>= xx + d and y < yy + d) {curr = curr->neChild;xx+=d;}
			if(x>= xx + d and y>= yy + d) {curr = curr->seChild;xx+=d;yy+=d;}
		}
		return curr->element;
	}
		
}

PNG Quadtree::decompress() const{
	if(imageSize == 0) return PNG();
	else{
		PNG ret((size_t)imageSize, (size_t)imageSize);
		for(int i = 0; i< imageSize; i++){
			for(int j = 0; j< imageSize; j++){
				*ret(i,j) = getPixel(i,j);
			}
		}
		return ret;
	}
}

void Quadtree::rotateNode(QuadtreeNode *source){
	if(source->nwChild != NULL){
		QuadtreeNode * temp = source->nwChild;
		source->nwChild = source->swChild;
		source->swChild = source->seChild;
		source->seChild = source->neChild;
		source->neChild = temp;

		rotateNode(source->nwChild);
		rotateNode(source->neChild);
		rotateNode(source->swChild);
		rotateNode(source->seChild);
	}
}
		
void Quadtree::clockwiseRotate (){
	rotateNode(root);
}

int Quadtree::nodeDiff(QuadtreeNode* cRoot, QuadtreeNode * child) const{
	int r1 = (int)cRoot->element.red;	int r2 = (int)child->element.red;
	int g1 = (int)cRoot->element.green;	int g2 = (int)child->element.green;
	int b1 = (int)cRoot->element.blue;	int b2 = (int)child->element.blue;

	return  (r1 - r2)*(r1 - r2) + (b1 - b2)*(b1 -b2) + (g1 - g2)*(g1 - g2);  
}


void Quadtree::pruneNode(QuadtreeNode* source, int tolerance){
	
	if(prunable(source, source, tolerance)){
		clear(source->nwChild);
		clear(source->neChild);
		clear(source->swChild);
		clear(source->seChild);
	}
	else{
		pruneNode(source->nwChild, tolerance);
		pruneNode(source->neChild, tolerance);
		pruneNode(source->swChild, tolerance);
		pruneNode(source->seChild, tolerance);
	}
}

bool Quadtree::prunable(QuadtreeNode * source, QuadtreeNode * start, int tol)const{
	
	if (source ->nwChild == NULL) return true;
	return (prunable(source->nwChild, start, tol) && prunable(source->neChild, start, tol) &&
		prunable(source->swChild, start, tol) && prunable(source->seChild, start, tol) &&
		nodeDiff(source->nwChild, start) <= tol &&
		nodeDiff(source->neChild, start) <= tol &&
		nodeDiff(source->swChild, start) <= tol &&
		nodeDiff(source->seChild, start) <= tol);
}

void Quadtree::prune (int tolerance){
	pruneNode(root,tolerance);
}

int Quadtree::pruneSize (QuadtreeNode * source, int tolerance) const{
	if(source == NULL) return 0;
	int count = 0;
	if(prunable(source, source, tolerance)) count += 1;
	else count +=  	pruneSize(source->nwChild, tolerance)+
			pruneSize(source->neChild, tolerance)+
			pruneSize(source->swChild, tolerance)+
			pruneSize(source->seChild, tolerance);
	return count;
	
}

int Quadtree::pruneSize (int tolerance) const{
	return pruneSize(root, tolerance);
}

int Quadtree::idealPrune (int numLeaves) const{
	if(pruneSize(0)<= numLeaves)
		return 0;
	int trialLarge = 1, trialSmall = 0;
	while(pruneSize(trialLarge) > numLeaves){
		trialLarge *= 2;
	}
	while(trialLarge - trialSmall > 1){
	int c = (trialLarge + trialSmall)/2;
		if(pruneSize(c) > numLeaves)
			trialSmall = c;
		else
			trialLarge = c;
	}
	return trialLarge;
}

#include "image.h"
#include "scene.h"
#include <iostream>

using namespace std;

/**
_copy() function to be called by the
copy-constractor and the assignment operator.
**/

void Scene::_copy(const Scene & source){
	pictureNumber = source.pictureNumber;
	pictureList = new Image*[pictureNumber];
	xcoords = new int[pictureNumber];	
	ycoords = new int[pictureNumber];
	for (int i = 0; i < pictureNumber; i++){
		pictureList[i] = NULL;
		if(source.pictureList[i] != NULL){
			pictureList[i] = new Image();
			*pictureList[i] = *source.pictureList[i];
			xcoords[i] = source.xcoords[i];
			ycoords[i] = source.ycoords[i];
		}
	}
}

/**
_clear() function to be called by the destructor 
and the assignment operator of the Scene class.
**/

void Scene::_clear(){
	for (int i=0; i < pictureNumber; i++){
		delete pictureList[i];
	}

	delete [] pictureList;
	delete [] xcoords;
	delete [] ycoords;

	pictureList = NULL;
	xcoords = NULL;
	ycoords = NULL;

}

/**
Initializes this Scene object to be able to hold 
"max" number of images with indices 0 through max-1.
**/

Scene::Scene(int max){
	pictureNumber = max;
	pictureList = new Image*[max];
	xcoords = new int[max];
	ycoords = new int[max];
	for (int i = 0; i < max; i++){
		pictureList[i] = NULL;
	}
}

/**
The copy constructor makes this Scene 
an independent copy of the source.
**/

Scene::Scene(const Scene & source){
	//_clear();
	_copy(source);	
}

/**
Destructor for the Scene class.
**/

Scene::~Scene(){
	_clear();
}

/**
The assignment operator for the Scene class.
**/

Scene const & Scene::operator=(const Scene & source){
	if(&source == this)
		return *this;
	_clear();
	_copy(source);
	return *this;
}

/**
Modifies the size of the array of Image 
pointers without changing their indices.
**/

void Scene::changemaxlayers(int newmax){
	if(newmax == pictureNumber)
		{
		cout<<"no change was made"<<endl;
		return;
		}
	if(newmax < pictureNumber){
		bool checkIfNull = false;
		for(int i=newmax; i<pictureNumber; i++){
			if(pictureList[i] != NULL){
				checkIfNull = true;
				break;
			}
		}
		if(checkIfNull){
		cout<<"invalid newmax"<<endl;
		return;
		}
	}
	
	Scene copiedScene(pictureNumber);
	copiedScene._clear();
	copiedScene._copy(*this);
	_clear();
	pictureNumber = newmax;
		
	pictureList = new Image* [newmax];
	xcoords = new int [newmax];
	ycoords = new int [newmax];

	if(newmax > copiedScene.pictureNumber){
		for(int i = 0; i < copiedScene.pictureNumber; i++){
			pictureList[i] = NULL;
			if(copiedScene.pictureList[i] != NULL){
				xcoords[i] = copiedScene.xcoords[i];
				ycoords[i] = copiedScene.ycoords[i];
				pictureList[i] = new Image();
				*pictureList[i] = *copiedScene.pictureList[i];
			}

		}

		//fillinig the rest with Null
		for(int i=copiedScene.pictureNumber; i < newmax; i++)
			pictureList[i] = NULL;

	}
	if(newmax < copiedScene.pictureNumber){
		for(int i = 0; i < newmax; i++){
			pictureList[i] = NULL;
			if(copiedScene.pictureList[i] != NULL){
				xcoords[i] = copiedScene.xcoords[i];
				ycoords[i] = copiedScene.ycoords[i];
				pictureList[i] = new Image();
				*pictureList[i] = *copiedScene.pictureList[i];
			}
		}
	}
}


/**
This function will add a picture to the scene, by 
placing it in the array cell corresponding to the 
given index, and storing its x coordinate and y coordinate.
**/

void Scene::addpicture(const char *Filename, int index, int x, int y){
	if(index < 0 || index > pictureNumber -1)
		cout<<"index out of bounds"<<endl;
	else{
		delete pictureList[index];
		pictureList[index] = new Image();	
		pictureList[index]->readFromFile(Filename);
		xcoords[index] = x;
		ycoords[index] = y;
	}
}

/**
Moves an Image from one layer to another.
**/

void Scene::changelayer(int index, int newindex){
	if (index < 0 || index > pictureNumber - 1 || newindex < 0 || newindex >pictureNumber - 1){
		cout<<"invalid index"<<endl;
		return;
	}
	if (pictureList[index] == NULL){
		delete pictureList[newindex];
		pictureList[newindex] = NULL;
		return;
	}
		
	if (index == newindex)
		return;

	if (pictureList[newindex] != NULL)
		delete pictureList[newindex];

	xcoords[newindex] = xcoords[index];
	ycoords[newindex] = ycoords[index]; 
	pictureList[newindex] = pictureList[index];
	pictureList[index] = NULL;	

}

/**
Changes the x and y coordinates 
of the Image in the specified layer.
**/

void Scene::translate(int index, int xcoord, int ycoord){
	if (index < 0 || index > pictureNumber - 1 || pictureList[index] == NULL){
		cout<<"invalid index"<<endl;
		return;
	}
	xcoords[index] = xcoord;
	ycoords[index] = ycoord;
}

/**
Deletes the Image at the given index.
**/

void Scene::deletepicture(int index){
	if (index < 0 || index > pictureNumber - 1 || pictureList[index] == NULL){
		cout<<"invalid index"<<endl;
		return;
	}
	delete pictureList[index];
	pictureList[index] = NULL;
}

/**
This function will return a pointer to the Image 
at the specified index, not a copy of it.
**/

Image* Scene::getpicture(int index) const{
	if (index < 0 || index > pictureNumber - 1 || pictureList[index] == NULL){
		cout<<"invalid index"<<endl;
		return NULL;
	}
	else
		return pictureList[index];
}

/**
Draws the whole scene on one Image 
and returns that Image by value.
**/

Image Scene::drawscene() const{
	int width = 0, height = 0, currentX = 0, currentY = 0;
	for(int i = 0; i < pictureNumber; i++){
		if(pictureList[i] != NULL){
			if(width < (int)pictureList[i]-> width() + xcoords[i])
				width = (int)pictureList[i]-> width() + xcoords[i];

			if(height < (int)pictureList[i]-> height() + ycoords[i])
				 height = (int)pictureList[i]-> height() + ycoords[i];
		}
	}
	Image board;
	board.resize(width, height);
	for(int k=0; k < pictureNumber; k++){
		if(pictureList[k] != NULL){
			currentX = xcoords[k];
			currentY = ycoords[k];
			for(int i = 0; i < (int)pictureList[k]->width();i++){
				for(int j = 0; j < (int)pictureList[k]->height();j++){
					*board(currentX + i,currentY + j) = *(pictureList[k]->operator()(i,j));
				}
			}
		}
	}
	return board;
}



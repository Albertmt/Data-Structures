#include "image.h"
#include "rgbapixel.h"
#include <iostream>

using namespace std;

/**
Flips the image about a vertical line 
through its center by swapping pixels. 
**/

void Image::flipleft(){
	RGBAPixel *a = new RGBAPixel();
	for(int i=0; 2* i < (int)width();i++){
		for(int j=0;j < (int)height();j++){
			*a = *operator()(i,j);
			*operator()(i,j) = *operator()((int)width() - 1 - i,j);
			*operator()((int)width() - 1 - i,j) = *a;
		}
	}
	delete a;
}

/**
Makes each RGB component of each pixel 
equal to 255 minus its original value.
**/

void Image::invertcolors(){
	for(int i=0;i<(int)width();i++){
		for(int j=0;j<(int)height();j++){
			operator()(i,j)->red = 255 - operator()(i,j)->red;
			operator()(i,j)->green = 255 - operator()(i,j)->green;
			operator()(i,j)->blue = 255 - operator()(i,j)->blue;
		}
	}
}

/**
Adds r, g and b to the red, green, and 
blue parts of each pixel in the image.
**/

void Image::adjustbrightness(int r, int g, int b){
	for(int i=0;i<(int)width();i++){
		for(int j=0;j<(int)height();j++){
			if(operator()(i,j)->red + r > 255)
				operator()(i,j)->red = 255;
			else if (operator()(i,j)->red + r < 0)
				operator()(i,j)->red = 0;
			else operator()(i,j)->red += r;

			if(operator()(i,j)->green + g > 255)
				operator()(i,j)->green = 255;
			else if (operator()(i,j)->green + g < 0)
				operator()(i,j)->green = 0;
			else operator()(i,j)->green += g;

			if(operator()(i,j)->blue + b > 255)
				operator()(i,j)->blue = 255;
			else if (operator()(i,j)->blue + b < 0)
				operator()(i,j)->blue = 0;
			else operator()(i,j)->blue += b;
		}
	}
}

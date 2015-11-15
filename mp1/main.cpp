#include <iostream>
#include "png.h"

using namespace std; 

int main(){
	PNG *pic1 = new PNG("in.png");
	PNG *pic2 = new PNG(*pic1);

	int width =(int) pic1->width();
	int height = (int) pic2->height();

	for(int i = 0; i <width;i++){
		for(int j=0; j<height;j++){	
			(*(*pic2)(i,j)).red=(*(*pic1)(width - 1 - i, height - 1 - j)).red;
			(*(*pic2)(i,j)).green=(*(*pic1)(width - 1 - i, height - 1 - j)).green;
			(*(*pic2)(i,j)).blue=(*(*pic1)(width - 1 - i, height - 1 - j)).blue;
			(*(*pic2)(i,j)).alpha=(*(*pic1)(width - 1 - i, height - 1 - j)).alpha;
		}
	}
	
	(*pic2).writeToFile("out.png");
	
	delete pic1;
	delete pic2;
	
	return 0;
}

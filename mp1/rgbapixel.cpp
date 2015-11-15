#include <cstdint>
#include <iostream>
#include "rgbapixel.h"

RGBAPixel::RGBAPixel(){
	red = 255;
	green = 255;
	blue = 255;
	alpha = 255; 
}
RGBAPixel::RGBAPixel(uint8_t r,uint8_t g, uint8_t b){
	red = r;
	green = g;
	blue = b;
	alpha = 255;
}
// void RGBAPixel::printComponents(){
// 	std::cout<<"red = "<<red<<"\n green = "<<green<<"\n blue = "<<blue<<"\n alpha = "<<alpha<<"\n";
//}

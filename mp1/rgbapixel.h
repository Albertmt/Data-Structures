#ifndef RGBAPIXEL_H
#define RGBAPIXEL_H

#include <cstdint>

class RGBAPixel{
	public:
		RGBAPixel(uint8_t red, uint8_t green, uint8_t blue);
		RGBAPixel();

		uint8_t red;
		uint8_t green;
		uint8_t blue;
		uint8_t alpha;
};
#endif

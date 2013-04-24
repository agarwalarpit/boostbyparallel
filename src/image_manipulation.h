
#include "header.h"

#ifndef _IMAGE_MANIPULATION_
#define _IMAGE_MANIPULATION_

Image LoadImage (const char* path);
void SaveImage (const Image& img, const char* path);
Image RGBtoRGBA (const Image& input);
Image RGBAtoRGB (const Image& input);

#endif 
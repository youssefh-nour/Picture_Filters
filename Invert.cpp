#include <iostream>
#include "Image_Class.h"

using namespace std;

void Invert(Image& img) {
	//loop through each pixel in the image
	for (int i = 0;i < img.width; ++i) {
		for (int j = 0;j < img.height;++j) {
			//invert the pixel by subtracting the RGB values from 255
			for (int k = 0;k < 3;++k) {
				img(i, j, k) = 255 - img(i, j, k);

			}
		}
	}
}
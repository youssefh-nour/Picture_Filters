#include <iostream>
#include "Image_Class.h"

using namespace std;

void Grayscale(Image& image) {
	//loop through each pixel in the image
	for (int _x = 0; _x < image.width; ++_x) {
		for (int _y = 0; _y < image.height; ++_y) {
			//set the pixel to the average of the RGB values
			int R = image(_x, _y, 0);
			int G = image(_x, _y, 1);
			int B = image(_x, _y, 2);
			int gray = (R + G + B) / 3;

			for (int k = 0; k < 3; ++k) {
				image(_x, _y, k) = gray;
			}
		}
	}
}
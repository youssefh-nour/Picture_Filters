#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "Image_Class.h"
#include <fstream>
using namespace std;
void naturalSunlight(Image& image) {
	for (int _x = 0; _x < image.width; ++_x) {
		for (int _y = 0; _y < image.height; ++_y) {
			// Increase the red channel 20% and cap it at 255
			//Validation checks
			int R = image(_x, _y, 0) * 1.2;
			if (R < 255) {
				image(_x, _y, 0) = R;
			}
			else {
				image(_x, _y, 0) = 255;
			}
			// Increase the green channel 15% and cap it at 255
			int G = image(_x, _y, 1) * 1.15;
			if (G < 255) {
				image(_x, _y, 1) = G;
			}
			else {
				image(_x, _y, 1) = 255;
			}
			// Increase the blue channel 5% and cap it at 255
			int B = image(_x, _y, 2) * 1.05;
			if (B < 255) {
				image(_x, _y, 2) = B;
			}
			else {
				image(_x, _y, 2) = 255;
			}
		}
	}
}

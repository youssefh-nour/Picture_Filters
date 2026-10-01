#include <iostream>
#include "Image_Class.h"

void BlackWhite(Image &img) {
	for (int x = 0;x < img.width;x++) {
		for (int y = 0;y < img.height;y++) {

			int avg = ((img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3);

			if (avg >= 128) {
				img(x, y, 0) = 255;
				img(x, y, 1) = 255;
				img(x, y, 2) = 255;
			}
			else {
				img(x, y, 0) = 0;
				img(x, y, 1) = 0;
				img(x, y, 2) = 0;

			}
		}
	}
}

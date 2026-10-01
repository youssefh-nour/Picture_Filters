#include <iostream>
#include "Image_Class.h"

void RotateImage(Image &img, int degree) {
	int loops = degree / 90;
	//loop through each pixel in the image and rotate it by 90 degrees for the specified number of loops
	for (int k = 0;k < loops;k++) {

		Image newImg(img.height, img.width);

		for (int x = 0;x < img.width;x++) {
			//loop through each pixel in the image and set the corresponding pixel in the new image to the rotated position
			for (int y = 0;y < img.height;y++) {

				int newX = img.height - 1 - y;
				int newY = x;

				newImg(newX, newY, 0) = img(x, y, 0);
				newImg(newX, newY, 1) = img(x, y, 1);
				newImg(newX, newY, 2) = img(x, y, 2);
			}
		}
		img = newImg;
	}
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "Image_Class.h"
#include <fstream>
using namespace std;
Image mergeImages(Image& img1, Image& img2) {
	int newW;
	int newH;
	newW = min(img1.width, img2.width);
	newH = min(img1.height, img2.height);
	Image mergeImage(newW, newH);
	for (int _x = 0; _x < newW; ++_x) {
		for (int _y = 0; _y < newH;++_y) {
			for (int k = 0; k < 3;++k) {
				int result = (img1(_x, _y, k) + img2(_x, _y, k)) / 2;

				mergeImage(_x, _y, k) = result;

			}
		}


	}


	return mergeImage;


}


int main() {
	Image img1("luffy.jpg");
	Image img2("Cry.jpg");
	Image NEW = mergeImages(img1, img2);

	NEW.saveImage("merged.png");


	return 0;
}
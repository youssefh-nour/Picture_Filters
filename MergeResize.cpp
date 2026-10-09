#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "Image_Class.h"
#include <fstream>
using namespace std;
Image mergeResize(Image& img1, Image& img2) {
	int newW;
	int newH;
	newW = max(img1.width, img2.width);
	newH = max(img1.height, img2.height);
	Image mergedImage(newW, newH);
	for (int _x = 0; _x < newW;++_x) {
		int x1 = _x * (img1.width / newW);
		int x2 = _x * (img2.width / newW);
		for (int _y = 0; _y < newH; ++_y) {
			int y1 = _y * (img1.height / newH);
			int y2 = _y * (img2.height / newH);
			for (int k = 0; k < 3; ++k) {
				int result = (img1(x1, y1, k) + img2(x2, y2, k)) / 2;
				mergedImage(_x, _y, k) = result;


			}
		}
	}
	return mergedImage;
}
int main() {
	Image img1("luffy.jpg");
	Image img2("Cry.jpg");
	Image NEW = mergeResize(img1, img2);

	NEW.saveImage("Resize.png");


	return 0;
}
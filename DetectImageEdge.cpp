#include <iostream>
#include<cmath>
#include "Image_Class.h"
using namespace std;

void detectimageedge(Image& img) {

	for (int x = 0;x < img.width;x++) {
		for (int y = 0;y < img.height;y++) {

			int avg = (img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3;
			img(x, y, 0) = avg;
			img(x, y, 1) = avg;
			img(x, y, 2) = avg;
		}
	}
	Image edgeimage(img.width, img.height);
	int edgelimit = 30;

	for (int x = 0;x < img.width - 1;x++) {
		for (int y = 0;y < img.height - 1;y++) {

			int current = img(x, y, 0);
			int right = img(x + 1, y, 0);
			int buttom = img(x, y + 1, 0);

			if (abs(current - buttom) > edgelimit || abs(current - right) > edgelimit) {

				edgeimage(x, y, 0) = 0;
				edgeimage(x, y, 1) = 0;
				edgeimage(x, y, 2) = 0;

			}
			else {
				edgeimage(x, y, 0) = 255;
				edgeimage(x, y, 1) = 255;
				edgeimage(x, y, 2) = 255;
			}
		}
	}
	img = edgeimage;
}

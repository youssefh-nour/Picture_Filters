#include<iostream>
#include<algorithm>
#include "Image_Class.h"

using namespace std;
void oldTVFilter(Image& img) {

	const int shift = 2;
	int w = img.width;
	int h = img.height;

	Image src = img;

	for (int y = 0;y < h;y++) {
		for (int x = 0;x < w;x++) {

			int xr = max(0, x - shift);
			int xb = min(w - 1, x + shift);

			img(x, y, 0) = src(xr, y, 0);
			img(x, y, 1) = src(x, y, 1);
			img(x, y, 2) = src(xb, y, 2);

			if (y % 2 == 0) {
				img(x, y, 0) = img(x, y, 0) * 3 / 4;
				img(x, y, 1) = img(x, y, 1) * 3 / 4;
				img(x, y, 2) = img(x, y, 2) * 3 / 4;
			}
		}
	}
}

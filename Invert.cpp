#include <iostream>
#include "Image_Class.h"

using namespace std;

void invert_img_fil(Image& img) {
	for (int i = 0;i < img.width; ++i) {
		for (int j = 0;j < img.height;++j) {
			for (int k = 0;k < 3;++k) {
				img(i, j, k) = 255 - img(i, j, k);

			}
		}
	}
}
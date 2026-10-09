#include<iostream>
#include "Image_Class.h"

void purple_tint(Image& img) {
	for (int i = 0;i < img.width;++i) {
	    for (int j = 0;j < img.height;++j) {

			int new_red= img(i, j, 0) * 0.6;
		    int new_green = img(i, j, 1) * 0.4;
		    int new_blue = img(i, j, 2) *0.9;
		    if (new_blue > 255) new_blue = 255;
			img(i, j, 0) = new_red;
			img(i, j, 1) = new_green;
		    img(i, j, 2) = new_blue;


	    }
	}
}

#include <iostream>
#include "Image_Class.h"

void lighten_darken_fil(Image& img, char choice) {
	//loop through each pixel in the image and lighten or darken it based on the user's choice
	int val = 70;
	for (int i = 0;i < img.width;++i) {
		for (int j = 0;j < img.height;++j) {
			//loop through each color channel (RGB) and adjust the pixel value based on the user's choice
			for (int k = 0;k < 3;++k) {
				int newcolor=img(i,j,k);
				if (choice == 'L' or choice == 'l')
					newcolor =img(i,j,k) * 1.5;
				if (choice == 'D' or choice == 'd')
					newcolor = (img(i, j, k) * 0.5);
				if (newcolor > 255) newcolor = 255;
				if (newcolor < 0) newcolor = 0;
				img(i, j, k) = newcolor;
			}
		}
	}
}

#include <iostream>
#include "Image_Class.h"
using namespace std;
void FlipHorizontal(Image& image) {
	//loop through each pixel in the image
	for (int _x = 0; _x < image.width / 2; ++_x) {
		for (int _y = 0; _y < image.height; ++_y) {
			//swap the pixel with the corresponding pixel on the other side of the image
			for (int k = 0; k < 3; ++k) {
				unsigned char Htemp = image(_x, _y, k);
				image(_x, _y, k) = image(image.width - 1 - _x, _y, k);
				image(image.width - 1 - _x, _y, k) = Htemp;

			}
		}
	}
}


int main() {
	Image image("luffy.jpg");

	FlipHorizontal(image);

	image.saveImage("flip.png");



return 0;

}
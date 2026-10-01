#include <iostream>
#include "Image_Class.h"
using namespace std;
void flipVertical(Image& image) {
	for (int _x = 0; _x < image.width; ++_x) {
		for (int _y = 0; _y < image.height / 2; ++_y) {
			for (int k = 0; k < 3; ++k) {
				unsigned char Vtemp = image(_x, _y, k);
				image(_x, _y, k) = image(_x, image.height - 1 - _y, k);
				image(_x, image.height - 1 - _y, k) = Vtemp;

			}

		}
	}
}


int main() {
	Image image("luffy.jpg");

	flipVertical(image);

	image.saveImage("Vflip.png");



return 0;

}
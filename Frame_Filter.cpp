#include <iostream>
#include "Image_Class.h"

using namespace std;

void addFrame(Image& image, int thickness, int r, int g, int b) {
	for (int _x = 0;_x < image.width; ++_x) {
		for (int _y = 0;_y < image.height; ++_y) {
			if (_x < thickness || _x >= image.width - thickness || _y < thickness || _y >= image.height - thickness) {
				image(_x, _y, 0) = r;
				image(_x, _y, 1) = g;
				image(_x, _y, 2) = b;
			}
		}
	}
}
void addFancyFrame(Image& image, int thickness, int r, int g, int b) {
	for (int _x = 0;_x < image.width; ++_x) {
		for (int _y = 0;_y < image.height; ++_y) {
			if (_x < (thickness + 8) || _x >= image.width - (thickness + 8) || _y < (thickness + 8) || _y >= image.height - (thickness + 8)) {
				image(_x, _y, 0) = r;
				image(_x, _y, 1) = g;
				image(_x, _y, 2) = b;
				if (_x < (thickness + 5) || _x >= image.width - (thickness + 5) || _y < (thickness + 5) || _y >= image.height - (thickness + 5)) {
					image(_x, _y, 0) = 255;
					image(_x, _y, 1) = 255;
					image(_x, _y, 2) = 255;
					if (_x < thickness || _x >= image.width - thickness || _y < thickness || _y >= image.height - thickness) {
						image(_x, _y, 0) = r;
						image(_x, _y, 1) = g;
						image(_x, _y, 2) = b;
					}		
				}
			}
		}
	}
}


int main() { 
	Image image("luffy.jpg");
	int thickness;
	int r;
	int g;
	int b;
    
	cout << " Enter Frame thickness: ";
	cin >> thickness;

	cout << " Enter red: ";
	cin >> r;

	cout << "Enter green: ";
	cin >> g;

	cout << "Enter blue: ";
	cin >> b;


	addFancyFrame(image, thickness, r, g, b); 
	image.saveImage("fancy.png");
	
    return 0;
}
#include <iostream>
#include "Image_Class.h"

using namespace std;

void AddFrame(Image& image, int thickness, int r, int g, int b) {
	//loop through each pixel in the image
	for (int _x = 0;_x < image.width; ++_x) {
		for (int _y = 0;_y < image.height; ++_y) {
			//set the pixel to the specified color if it is within the frame thickness
			if (_x < thickness || _x >= image.width - thickness || _y < thickness || _y >= image.height - thickness) {
				image(_x, _y, 0) = r;
				image(_x, _y, 1) = g;
				image(_x, _y, 2) = b;
			}
		}
	}
}

void AddFancyFrame(Image& image, int thickness, int r, int g, int b) {
	//loop through each pixel in the image
	for (int _x = 0;_x < image.width; ++_x) {
		for (int _y = 0;_y < image.height; ++_y) {
			//set the pixel to the specified color if it is within the frame thickness, with a white border around the frame
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

//test
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


	AddFancyFrame(image, thickness, r, g, b); 
	image.saveImage("fancy.png");
	
    return 0;
}
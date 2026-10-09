#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>
#include "Image_Class.h"
#include <fstream>
#include <cmath>
using namespace std;
Image skewImage(Image& image, double degrees) {
	double radians = degrees * (3.14159 / 180);

	int newW = image.width + (int)(tan(radians) * (image.height - 1));
	int newH = image.height;

	Image skewedimage(newW, newH);

	for (int _x = 0; _x < newW; ++_x) {
		for (int _y = 0; _y < newH; ++_y) {
			for (int k = 0; k < 3; ++k) {
				skewedimage(_x, _y, k) = 255;
			}
		}
	}

	for (int _y = 0; _y < image.height; ++_y) {
		int shift = (int)(((image.height - 1) - _y) * tan(radians));
		for (int _x = 0; _x < image.width; ++_x) {
			for (int k = 0; k < 3; ++k) {
				skewedimage(_x + shift, _y, k) = image(_x, _y, k);
			}
		}
	}

	return skewedimage;
}


int main() {
	Image image("luffy.jpg");

	double degrees;
	cout << "Enter skew angle (0 to 90, exclusive): ";
	cin >> degrees;
	while (degrees <= 0 || degrees >= 90) {
		cout << "Invalid angle. Try again: ";
		cin >> degrees;
	}

	Image skewed = skewImage(image, degrees);
	skewed.saveImage("skew.png");
	cout << "saved" << endl;
	cin.ignore();
	cin.get();


	return 0;



}
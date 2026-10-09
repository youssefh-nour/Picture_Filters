#include <iostream>
#include "Image_Class.h"
using namespace std;

//To make the filter, maximize all R values for all pixels
//and set the B values to the G values for all pixels. This will create an infrared effect on the image.

void InfraRed(Image& image) {
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            image(x, y, 0) = 255; // Set the red channel to maximum
            image(x, y, 2) = image(x, y, 1); // Set the blue channel to the value of the green channel
        }
    }
}

//test
int main() {
    Image image = Image("luffy.jpg");
    InfraRed(image);
    image.saveImage("infrared_image.png");
    return 0;
}
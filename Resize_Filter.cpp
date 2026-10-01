#include <iostream>
#include "Image_Class.h"

using namespace std;

void Resize_Filter(Image& image, int height, int width){
    //new image with the new dimensions (should instead modify the original image, but for now we will create a new one )
    Image resizedImage(width, height);
    //For every pixel in the new image:
    //Find the corresponding position in the old image
    //Calculate the appropriate pixel color
    //Put that color in the new image
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Calculate the corresponding position in the old image
            int oldX = x * image.width / width;
            int oldY = y * image.height / height;

            // Ensure we don't go out of bounds
            if (oldX >= image.width) oldX = image.width - 1;
            if (oldY >= image.height) oldY = image.height - 1;

            // Copy the pixel color from the old image to the new image
            for (int c = 0; c < image.channels; ++c) {
                resizedImage.imageData[(y * width + x) * image.channels + c] =
                    image.imageData[(oldY * image.width + oldX) * image.channels + c];
            }
        }
    }
    image = resizedImage;
}

int main() {
    // Example usage
    Image image("luffy.jpg");
    Resize_Filter(image, 800, 600);
    image.saveImage("resized_image.png");
    return 0;
}
//yarab yeshta8al fi yom men el ayam
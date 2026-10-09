#include <iostream>
#include "Image_Class.h"
#include <vector>
using namespace std;

//To make the filter, we need to make a custom kernel
/*A "blur" kernel is a matrix that averages the pixel values of an image to create a smoothing effect. 
The size of the kernel determines the strength of the blur effect. 
A common choice for a blur kernel is a 3x3 matrix where each element has the value of 1/9, 
which means that each pixel's new value will be the average of itself and its 8 neighbors.*/

//But we can make a custom blur level by changing the values in the kernel.

/* To make it possible without the time space complexity exploding into an absurd O(hwr^2),
We can use an additional function that will make a custom table
This will gather the sum of pixels in a 
given radius and divide it by the number of pixels in that radius to get the average value for the kernel.
This function can be used in the main Blur function to create a custom kernel based on the desired blur level. 
Plus, it will simplify the code and make it more optimized and efficient overall
*/

//This filter is hard. Please go easy on us explaining it, engineer TA sir/madam

//use vectors because each image can have different sizes and we don't want to waste memory on a fixed size array (and  safer, of course)

vector<vector<long long>> Table(Image& image, int channel) {
    vector<vector<long long>> table(image.height+1, vector<long long>(image.width+1, 0));
    for (int y = 1; y <= image.height; ++y) {
        for (int x = 1; x <= image.width; ++x) {
            table[y][x] = image(x - 1, y - 1, channel);
            table[y][x] += table[y - 1][x] + table[y][x - 1] - table[y - 1][x - 1];
        }
    }
    return table;
}

void Blur(Image& image, int radius) {
    //verify correct radius first
    if (radius <= 0 || radius > max(image.width, image.height)) {
        cout << "invalid blur level" << endl;
        return;
    }
    // Create tables for each channel
    vector<vector<long long>> tables[3];
    for (int channel = 0; channel < 3; ++channel) {
        tables[channel] = Table(image, channel);
    }
    // Create a new image to store the blurred result
    Image blurredImage(image.width, image.height);
    // Apply the blur effect using the tables
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
                int x1 = max(0, x - radius);
                int y1 = max(0, y - radius);
                int x2 = min(image.width - 1, x + radius);
                int y2 = min(image.height - 1, y + radius);
            for (int channel = 0; channel < 3; ++channel) {
                long long sum = tables[channel][y2 + 1][x2 + 1] - tables[channel][y1][x2 + 1] - tables[channel][y2 + 1][x1] + tables[channel][y1][x1];
                int count = (x2 - x1 + 1) * (y2 - y1 + 1);
                blurredImage(x, y, channel) = static_cast<unsigned char>(sum / count);
            }
        }
    }
    // Copy the blurred image data back to the original image
    image = blurredImage;
}


//test
int main() {
    // Example usage
    Image image("luffy.jpg");
    Blur(image, 4);
    image.saveImage("blurred_image.png");
    return 0;
}
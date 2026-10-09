#include <iostream>
#include "Image_Class.h"
#include <vector>
using namespace std;

// This function applies an oil painting effect to the given image.
//radius 3, 8 buckets 
// The oil painting effect works by replacing each pixel's color with the average color of its neighboring pixels within a specified radius.
void OilPainting(Image& image, int radius) {
    // Verify correct radius first
    if (radius <= 0 || radius > max(image.width, image.height)) {
        cout << "invalid oil painting level" << endl;
        return;
    }

    // Create a new image to store the oil painting result
    Image oilPaintedImage(image.width, image.height);

    // Apply the oil painting effect
    for (int y = 0; y < image.height; ++y) {
        for (int x = 0; x < image.width; ++x) {
            int x1 = max(0, x - radius);
            int y1 = max(0, y - radius);
            int x2 = min(image.width - 1, x + radius);
            int y2 = min(image.height - 1, y + radius);

            // Initialize buckets for color averaging
            vector<int> redBuckets(8, 0);
            vector<int> greenBuckets(8, 0);
            vector<int> blueBuckets(8, 0);
            vector<int> countBuckets(8, 0);

            // Iterate through the neighboring pixels within the specified radius
            for (int ny = y1; ny <= y2; ++ny) {
                for (int nx = x1; nx <= x2; ++nx) {
                    int red = image(nx, ny, 0);
                    int green = image(nx, ny, 1);
                    int blue = image(nx, ny, 2);

                    // Determine the bucket index based on the pixel's color intensity
                    int bucketIndex = (red + green + blue) / 3 * 8 / 256;

                    // Accumulate color values in the corresponding buckets
                    redBuckets[bucketIndex] += red;
                    greenBuckets[bucketIndex] += green;
                    blueBuckets[bucketIndex] += blue;
                    countBuckets[bucketIndex]++;
                }
            }

            // Find the bucket with the maximum count and calculate the average color
            int maxCount = 0;
            int avgRed = 0, avgGreen = 0, avgBlue = 0;

            for (int i = 0; i < 8; ++i) {
                if (countBuckets[i] > maxCount) {
                    maxCount = countBuckets[i];
                    avgRed = redBuckets[i] / maxCount;
                    avgGreen = greenBuckets[i] / maxCount;
                    avgBlue = blueBuckets[i] / maxCount;
                }
            }

            // Set the color of the current pixel in the oil painting image
            oilPaintedImage(x, y, 0) = avgRed;
            oilPaintedImage(x, y, 1) = avgGreen;
            oilPaintedImage(x, y, 2) = avgBlue;
        }
    }

    // Replace the original image with the oil painting result
    image = oilPaintedImage;
}

//test
int main() {
    Image image("luffy.jpg"); // Load an image
    OilPainting(image, 3); // Apply oil painting effect with radius 3
    image.saveImage("OilPainting.jpg"); // Save the result
    return 0;
}

/**
 * @File  : Image_Class.h
 * @brief : This file contains the declaration of the Image class.
 *
 * @authors : Shehab Diab, Youssef Mohamed , Nada Ahmed.
 *                       Dr Mohamed El-Ramely ,
 * @copyright : FCAI Cairo University
 * @version   : v2.0 (Added operator= and copy constructor)
 * @date      : 27/3/2024
 */


// stb_image header definitions
#ifndef _IMAGE_CLASS_H
#define _IMAGE_CLASS_H
#include<cmath>
#include<cstring>
#include<vector>
#include "stb_image.h"
#include "stb_image_write.h"

#define ll long long
#define PNG_TYPE 1
#define BMP_TYPE 2
#define TGA_TYPE 3
#define JPG_TYPE 4
#define UNSUPPORTED_TYPE -1

#define pixel unsigned int
#include <iostream>
#include <exception>


/**
 * @class Image
 * @brief Represents an image with functionalities for loading, saving, and manipulating pixels.
 */
class Image {
private:
    /**
     * @brief Checks if the given filename has a valid extension.
     *
     * @param filename The filename to check.
     * @return True if the filename has a valid extension, false otherwise.
     */
    bool isValidFilename(const std::string& filename) {
        const char* extension = strrchr(filename.c_str(), '.');
        if (extension == nullptr) {
            std::cerr << "Invalid filename: " << filename << std::endl;
            return false;
        }

        return true;
    }

    /**
     * @brief Determines the image type based on the file extension.
     *
     * @param extension The file extension to determine the type.
     * @return The type of image format.
     */

    short getExtensionType(const char* extension) {
        if (strcmp(extension, ".png") == 0) {
            return PNG_TYPE;
        }
        if (strcmp(extension, ".bmp") == 0) {
            return BMP_TYPE;
        }
        if (strcmp(extension, ".tga") == 0) {
            return TGA_TYPE;
        }
        if (strcmp(extension, ".jpg") == 0 || strcmp(extension, ".jpeg") == 0) {
            return JPG_TYPE;
        }

        std::cerr << "Unsupported image format: " << extension << std::endl;
        return UNSUPPORTED_TYPE;
    }

private:
    std::string filename; ///< Stores the filename of the image.

public:
    int width = 0; ///< Width of the image.
    int height = 0; ///< Height of the image.
    int channels = 3; ///< Number of color channels in the image.
    unsigned char* imageData = nullptr; ///< Pointer to the image data.

    /**
     * @brief Default constructor for the Image class.
     */
    Image() = default;

    /**
     * @brief Constructor that loads an image from the specified filename.
     *
     * @param filename The filename of the image to load.
     */
    Image(std::string filename) : filename((filename)) {
        loadNewImage(this->filename);
    }

    /**
     * @brief Constructor that creates an image with the specified dimensions.
     *
     * @param mWidth The width of the image.
     * @param mHeight The height of the image.
     */
    Image(int mWidth, int mHeight) {
        this->width = mWidth;
        this->height = mHeight;
        this->imageData = (unsigned char*)malloc(mWidth * mHeight * this->channels);
    }

    /**
     * @brief Constructor that creates an image by copying another image.
     *
     * @param other The Image we want to copy.
     */
    Image(const Image& other) {
        *this = other;
    }

    /**
     * @brief Overloading the assignment operator.
     *
     * @param image The Image we want to copy.
     *
     * @return *this after copying data.
     */

    Image& operator=(const Image& image) {
        if (this == &image){
            return *this;
        }

        stbi_image_free(this->imageData);
        this->imageData = nullptr;

        this->width = image.width;
        this->height = image.height;
        this->channels = image.channels;
        imageData = static_cast<unsigned char*>(malloc(width * height * channels));

        for (int i = 0; i < image.width * image.height * this->channels; i++) {
            this->imageData[i] = image.imageData[i];
        }

        return *this;
    }

    /**
     * @brief Destructor for the Image class.
     */
    ~Image() {
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }
        this->width = 0;
        this->height = 0;
        this->imageData = nullptr;
    }

    /**
     * @brief Loads a new image from the specified filename.
     *
     * @param filename The filename of the image to load.
     * @return True if the image is loaded successfully, false otherwise.
     * @throws std::invalid_argument If the filename or file format is invalid.
     */
    bool loadNewImage(const std::string& filename) {
        if (!isValidFilename(filename)) {
            std::cerr << "Couldn't Load Image" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        const char* extension = strrchr(filename.c_str(), '.');
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE) {
            std::cerr << "Unsupported File Format" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }
        if (imageData != nullptr) {
            stbi_image_free(imageData);
        }

        imageData = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);
        this->channels = 3;
        // Mohamed Mahmoud khalifa - Class 2024-2028 - 2025-10-14
        // Force image to load as RGB (3 channels) to fix issues with screenshots png 
        // containing an unnecessary 4th (alpha) channel.

        if (imageData == nullptr) {
            std::cerr << "File Doesn't Exist" << '\n';
            throw std::invalid_argument("Invalid filename, File Does not Exist");
        }

        return true;
    }

    /**
     * @brief Saves the image to the specified output filename.
     *
     * @param outputFilename The filename to save the image.
     * @return True if the image is saved successfully, false otherwise.
     * @throws std::invalid_argument If the output filename or file format is invalid.
     */

    bool saveImage(const std::string& outputFilename) {
        if (!isValidFilename(outputFilename)) {
            std::cerr << "Not Supported Format" << '\n';
            throw std::invalid_argument("The file extension does not exist");
        }

        // Determine image type based on filename extension
        const char* extension = strrchr(outputFilename.c_str(), '.');
        short extensionType = getExtensionType(extension);
        if (extensionType == UNSUPPORTED_TYPE) {
            std::cerr << "File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported" << '\n';
            throw std::invalid_argument("File Extension is not supported, Only .JPG, JPEG, .BMP, .PNG, .TGA are supported");
        }

        if (extensionType == PNG_TYPE) {
            stbi_write_png(outputFilename.c_str(), width, height, STBI_rgb, imageData, width * 3);
        }
        else if (extensionType == BMP_TYPE) {
            stbi_write_bmp(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        }
        else if (extensionType == TGA_TYPE) {
            stbi_write_tga(outputFilename.c_str(), width, height, STBI_rgb, imageData);
        }
        else if (extensionType == JPG_TYPE) {
            stbi_write_jpg(outputFilename.c_str(), width, height, STBI_rgb, imageData, 90);
        }

        return true;
    }

    /**
     * @brief Gets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0 for red, 1 for green, 2 for blue).
     * @return Reference to the pixel value.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    unsigned char& getPixel(int x, int y, int c) {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }

    const unsigned char& getPixel(int x, int y, int c) const {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        return imageData[(y * width + x) * channels + c];
    }
    /**
     * @brief Sets the pixel value at the specified position and channel.
     *
     * @param x The x-coordinate of the pixel.
     * @param y The y-coordinate of the pixel.
     * @param c The color channel index (0 for red, 1 for green, 2 for blue).
     * @param value The new value to set.
     * @throws std::out_of_range If the coordinates or channel index is out of bounds.
     */
    void setPixel(int x, int y, int c, unsigned char value) {
        if (x > width || x < 0) {
            std::cerr << "Out of width bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed width value");
        }
        if (y > height || y < 0) {
            std::cerr << "Out of height bounds" << '\n';
            throw std::out_of_range("Out of bounds, Cannot exceed height value");
        }
        if (c < 0 || c > 2) {
            std::cerr << "Out of channels bounds" << '\n';
            throw std::out_of_range("Out of bounds, You only have 3 channels in RGB");
        }

        imageData[(y * width + x) * channels + c] = value;
    }

    /**
     * @brief Overloaded function call operator to access pixels.
     *
     * @param row The row index of the pixel.
     * @param col The column index of the pixel.
     * @param channel The color channel index (0 for red, 1 for green, 2 for blue).
     * @return Reference to the pixel value.
     */
    const unsigned char& operator()(int row, int col, int channel) const {
        return getPixel(row, col, channel);
    }

    unsigned char& operator()(int row, int col, int channel) {
        return getPixel(row, col, channel);
    }
    // ------------------- Filter Functions -------------------

    void invert_img_fil() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    (*this)(i, j, k) = 255 - (*this)(i, j, k);
                }
            }
        }
    }

    void ConvertToBlackAndWhite() {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int avg = (((*this)(x, y, 0) + (*this)(x, y, 1) + (*this)(x, y, 2)) / 3);
                if (avg >= 128) {
                    (*this)(x, y, 0) = 255;
                    (*this)(x, y, 1) = 255;
                    (*this)(x, y, 2) = 255;
                } else {
                    (*this)(x, y, 0) = 0;
                    (*this)(x, y, 1) = 0;
                    (*this)(x, y, 2) = 0;
                }
            }
        }
    }

    void lighten_darken_fil(char choice) {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int newcolor = (*this)(i, j, k);
                    if (choice == 'L' || choice == 'l')
                        newcolor = (*this)(i, j, k) * 1.5;
                    if (choice == 'D' || choice == 'd')
                        newcolor = ((*this)(i, j, k) * 0.5);
                    if (newcolor > 255) newcolor = 255;
                    if (newcolor < 0) newcolor = 0;
                    (*this)(i, j, k) = newcolor;
                }
            }
        }
    }

    void RotateImage(int degree) {
        int loops = degree / 90;
        for (int k = 0; k < loops; k++) {
            Image newImg(height, width);
            for (int x = 0; x < width; x++) {
                for (int y = 0; y < height; y++) {
                    int newX = height - 1 - y;
                    int newY = x;
                    newImg(newX, newY, 0) = (*this)(x, y, 0);
                    newImg(newX, newY, 1) = (*this)(x, y, 1);
                    newImg(newX, newY, 2) = (*this)(x, y, 2);
                }
            }
            *this = newImg;
        }
    }

    void cropimage(int startx, int starty, int new_wid, int new_h) {
        Image cropped_img(new_wid, new_h);
        for (int i = 0; i < new_wid; ++i) {
            for (int j = 0; j < new_h; ++j) {
                for (int k = 0; k < 3; ++k) {
                    cropped_img(i, j, k) = (*this)(startx + i, starty + j, k);
                }
            }
        }
        *this = cropped_img;
    }

    void purple_tint() {
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                int new_red = (*this)(i, j, 0) * 0.6;
                int new_green = (*this)(i, j, 1) * 0.4;
                int new_blue = (*this)(i, j, 2) * 0.9;
                if (new_blue > 255) new_blue = 255;
                (*this)(i, j, 0) = new_red;
                (*this)(i, j, 1) = new_green;
                (*this)(i, j, 2) = new_blue;
            }
        }
    }

    void detectimageedge() {
        for (int x = 0; x < width; x++) {
            for (int y = 0; y < height; y++) {
                int avg = ((*this)(x, y, 0) + (*this)(x, y, 1) + (*this)(x, y, 2)) / 3;
                (*this)(x, y, 0) = avg;
                (*this)(x, y, 1) = avg;
                (*this)(x, y, 2) = avg;
            }
        }
        Image edgeimage(width, height);
        int edgelimit = 30;

        for (int x = 0; x < width - 1; x++) {
            for (int y = 0; y < height - 1; y++) {
                int current = (*this)(x, y, 0);
                int right = (*this)(x + 1, y, 0);
                int buttom = (*this)(x, y + 1, 0);

                if (abs(current - buttom) > edgelimit || abs(current - right) > edgelimit) {
                    edgeimage(x, y, 0) = 0;
                    edgeimage(x, y, 1) = 0;
                    edgeimage(x, y, 2) = 0;
                } else {
                    edgeimage(x, y, 0) = 255;
                    edgeimage(x, y, 1) = 255;
                    edgeimage(x, y, 2) = 255;
                }
            }
        }
        *this = edgeimage;
    }

    void oldTVFilter() {
        const int shift = 2;
        int w = width;
        int h = height;
        Image src = *this;

        for (int y = 0; y < h; y++) {
            for (int x = 0; x < w; x++) {
                int xr = std::max(0, x - shift);
                int xb = std::min(w - 1, x + shift);

                (*this)(x, y, 0) = src(xr, y, 0);
                (*this)(x, y, 1) = src(x, y, 1);
                (*this)(x, y, 2) = src(xb, y, 2);

                if (y % 2 == 0) {
                    (*this)(x, y, 0) = (*this)(x, y, 0) * 3 / 4;
                    (*this)(x, y, 1) = (*this)(x, y, 1) * 3 / 4;
                    (*this)(x, y, 2) = (*this)(x, y, 2) * 3 / 4;
                }
            }
        }
    }
    // ------------------- Additional Filters -------------------

    void flipHorizontal() {
        for (int _x = 0; _x < width / 2; ++_x) {
            for (int _y = 0; _y < height; ++_y) {
                for (int k = 0; k < 3; ++k) {
                    unsigned char Htemp = (*this)(_x, _y, k);
                    (*this)(_x, _y, k) = (*this)(width - 1 - _x, _y, k);
                    (*this)(width - 1 - _x, _y, k) = Htemp;
                }
            }
        }
    }

    void flipVertical() {
        for (int _x = 0; _x < width; ++_x) {
            for (int _y = 0; _y < height / 2; ++_y) {
                for (int k = 0; k < 3; ++k) {
                    unsigned char Vtemp = (*this)(_x, _y, k);
                    (*this)(_x, _y, k) = (*this)(_x, height - 1 - _y, k);
                    (*this)(_x, height - 1 - _y, k) = Vtemp;
                }
            }
        }
    }

    void grayscale() {
        for (int _x = 0; _x < width; ++_x) {
            for (int _y = 0; _y < height; ++_y) {
                int R = (*this)(_x, _y, 0);
                int G = (*this)(_x, _y, 1);
                int B = (*this)(_x, _y, 2);
                int gray = (R + G + B) / 3;

                for (int k = 0; k < 3; ++k) {
                    (*this)(_x, _y, k) = gray;
                }
            }
        }
    }

    void mergeImages(const Image& img2) {
        int newW = std::min(this->width, img2.width);
        int newH = std::min(this->height, img2.height);
        Image mergeImage(newW, newH);

        for (int _x = 0; _x < newW; ++_x) {
            for (int _y = 0; _y < newH; ++_y) {
                for (int k = 0; k < 3; ++k) {
                    int result = ((*this)(_x, _y, k) + img2(_x, _y, k)) / 2;
                    mergeImage(_x, _y, k) = result;
                }
            }
        }
        *this = mergeImage;
    }

    void mergeResize(const Image& img2) {
        int newW = std::max(this->width, img2.width);
        int newH = std::max(this->height, img2.height);
        Image mergedImage(newW, newH);

        for (int _x = 0; _x < newW; ++_x) {
            int x1 = _x * (this->width / (double)newW);
            int x2 = _x * (img2.width / (double)newW);
            for (int _y = 0; _y < newH; ++_y) {
                int y1 = _y * (this->height / (double)newH);
                int y2 = _y * (img2.height / (double)newH);
                for (int k = 0; k < 3; ++k) {
                    int result = ((*this)(x1, y1, k) + img2(x2, y2, k)) / 2;
                    mergedImage(_x, _y, k) = result;
                }
            }
        }
        *this = mergedImage;
    }

    void naturalSunlight() {
        for (int _x = 0; _x < width; ++_x) {
            for (int _y = 0; _y < height; ++_y) {
                int R = (*this)(_x, _y, 0) * 1.2;
                (*this)(_x, _y, 0) = (R < 255) ? R : 255;

                int G = (*this)(_x, _y, 1) * 1.15;
                (*this)(_x, _y, 1) = (G < 255) ? G : 255;

                int B = (*this)(_x, _y, 2) * 1.05;
                (*this)(_x, _y, 2) = (B < 255) ? B : 255;
            }
        }
    }

    void skewImage(double degrees) {
        double radians = degrees * (3.14159265358979323846 / 180.0);
        int newW = width + (int)(tan(radians) * (height - 1));
        int newH = height;

        Image skewedimage(newW, newH);

        for (int _x = 0; _x < newW; ++_x) {
            for (int _y = 0; _y < newH; ++_y) {
                for (int k = 0; k < 3; ++k) {
                    skewedimage(_x, _y, k) = 255;
                }
            }
        }

        for (int _y = 0; _y < height; ++_y) {
            int shift = (int)(((height - 1) - _y) * tan(radians));
            for (int _x = 0; _x < width; ++_x) {
                for (int k = 0; k < 3; ++k) {
                    skewedimage(_x + shift, _y, k) = (*this)(_x, _y, k);
                }
            }
        }
        *this = skewedimage;
    }
    // ------------------- Frame Filters -------------------
    void AddFrame(int thickness, int r, int g, int b) {
        for (int _x = 0; _x < width; ++_x) {
            for (int _y = 0; _y < height; ++_y) {
                if (_x < thickness || _x >= width - thickness || _y < thickness || _y >= height - thickness) {
                    (*this)(_x, _y, 0) = r;
                    (*this)(_x, _y, 1) = g;
                    (*this)(_x, _y, 2) = b;
                }
            }
        }
    }

    void AddFancyFrame(int thickness, int r, int g, int b) {
        for (int _x = 0; _x < width; ++_x) {
            for (int _y = 0; _y < height; ++_y) {
                if (_x < (thickness + 8) || _x >= width - (thickness + 8) || _y < (thickness + 8) || _y >= height - (thickness + 8)) {
                    (*this)(_x, _y, 0) = r;
                    (*this)(_x, _y, 1) = g;
                    (*this)(_x, _y, 2) = b;
                    if (_x < (thickness + 5) || _x >= width - (thickness + 5) || _y < (thickness + 5) || _y >= height - (thickness + 5)) {
                        (*this)(_x, _y, 0) = 255;
                        (*this)(_x, _y, 1) = 255;
                        (*this)(_x, _y, 2) = 255;
                        if (_x < thickness || _x >= width - thickness || _y < thickness || _y >= height - thickness) {
                            (*this)(_x, _y, 0) = r;
                            (*this)(_x, _y, 1) = g;
                            (*this)(_x, _y, 2) = b;
                        }
                    }
                }
            }
        }
    }

    // ------------------- Resize Filter -------------------
    void Resize_Filter(int newHeight, int newWidth) {
        Image resizedImage(newWidth, newHeight);
        for (int y = 0; y < newHeight; ++y) {
            for (int x = 0; x < newWidth; ++x) {
                int oldX = x * width / newWidth;
                int oldY = y * height / newHeight;

                if (oldX >= width) oldX = width - 1;
                if (oldY >= height) oldY = height - 1;

                for (int c = 0; c < 3; ++c) {
                    resizedImage(x, y, c) = (*this)(oldX, oldY, c);
                }
            }
        }
        *this = resizedImage;
    }

    // ------------------- Blur Filter -------------------
    std::vector<std::vector<long long>> buildBlurTable(int channel) {
        std::vector<std::vector<long long>> table(height + 1, std::vector<long long>(width + 1, 0));
        for (int y = 1; y <= height; ++y) {
            for (int x = 1; x <= width; ++x) {
                table[y][x] = (*this)(x - 1, y - 1, channel);
                table[y][x] += table[y - 1][x] + table[y][x - 1] - table[y - 1][x - 1];
            }
        }
        return table;
    }

    void Blur(int radius) {
        if (radius <= 0 || radius > std::max(width, height)) return;

        std::vector<std::vector<long long>> tables[3];
        for (int channel = 0; channel < 3; ++channel) {
            tables[channel] = buildBlurTable(channel);
        }

        Image blurredImage(width, height);
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int x1 = std::max(0, x - radius);
                int y1 = std::max(0, y - radius);
                int x2 = std::min(width - 1, x + radius);
                int y2 = std::min(height - 1, y + radius);

                for (int channel = 0; channel < 3; ++channel) {
                    long long sum = tables[channel][y2 + 1][x2 + 1] - tables[channel][y1][x2 + 1] - tables[channel][y2 + 1][x1] + tables[channel][y1][x1];
                    int count = (x2 - x1 + 1) * (y2 - y1 + 1);
                    blurredImage(x, y, channel) = static_cast<unsigned char>(sum / count);
                }
            }
        }
        *this = blurredImage;
    }

    // ------------------- InfraRed Filter -------------------
    void InfraRed() {
        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                (*this)(x, y, 0) = 255;
                (*this)(x, y, 2) = (*this)(x, y, 1);
            }
        }
    }
 // ------------------- Oil Painting Filter (Filter 18) -------------------
    void OilPainting(int radius = 3) {
        if (radius <= 0 || radius > std::max(width, height)) return;

        Image oilPaintedImage(width, height);

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {
                int x1 = std::max(0, x - radius);
                int y1 = std::max(0, y - radius);
                int x2 = std::min(width - 1, x + radius);
                int y2 = std::min(height - 1, y + radius);

                std::vector<int> redBuckets(8, 0);
                std::vector<int> greenBuckets(8, 0);
                std::vector<int> blueBuckets(8, 0);
                std::vector<int> countBuckets(8, 0);

                for (int ny = y1; ny <= y2; ++ny) {
                    for (int nx = x1; nx <= x2; ++nx) {
                        int red = (*this)(nx, ny, 0);
                        int green = (*this)(nx, ny, 1);
                        int blue = (*this)(nx, ny, 2);

                        int bucketIndex = (red + green + blue) / 3 * 8 / 256;
                        if (bucketIndex > 7) bucketIndex = 7; // حماية من تجاوز أبعاد الفيكتور

                        redBuckets[bucketIndex] += red;
                        greenBuckets[bucketIndex] += green;
                        blueBuckets[bucketIndex] += blue;
                        countBuckets[bucketIndex]++;
                    }
                }

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

                oilPaintedImage(x, y, 0) = avgRed;
                oilPaintedImage(x, y, 1) = avgGreen;
                oilPaintedImage(x, y, 2) = avgBlue;
            }
        }
        *this = oilPaintedImage;
    }

};

#endif // _IMAGE_CLASS_H

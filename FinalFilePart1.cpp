#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Image_Class.h"
#include <fstream>
//Menu is starting line 180
using namespace std;

void Grayscale(Image& image) {
	//loop through each pixel in the image
	for (int _x = 0; _x < image.width; ++_x) {
		for (int _y = 0; _y < image.height; ++_y) {
			//set the pixel to the average of the RGB values
			int R = image(_x, _y, 0);
			int G = image(_x, _y, 1);
			int B = image(_x, _y, 2);
			int gray = (R + G + B) / 3;

			for (int k = 0; k < 3; ++k) {
				image(_x, _y, k) = gray;
			}
		}
	}
}

void BlackWhite(Image &img) {
	//loop through each pixel in the image
	for (int x = 0;x < img.width;x++) {
		for (int y = 0;y < img.height;y++) {

			int avg = ((img(x, y, 0) + img(x, y, 1) + img(x, y, 2)) / 3);
			//set the pixel to black or white based on the average value of the pixel
			if (avg >= 128) {
				img(x, y, 0) = 255;
				img(x, y, 1) = 255;
				img(x, y, 2) = 255;
			}
			else {
				img(x, y, 0) = 0;
				img(x, y, 1) = 0;
				img(x, y, 2) = 0;

			}
		}
	}
}

void Invert(Image& img) {
	//loop through each pixel in the image
	for (int i = 0;i < img.width; ++i) {
		for (int j = 0;j < img.height;++j) {
			//invert the pixel by subtracting the RGB values from 255
			for (int k = 0;k < 3;++k) {
				img(i, j, k) = 255 - img(i, j, k);

			}
		}
	}
}

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
void FlipVertical(Image& image) {
	//loop through each pixel in the image
	for (int _x = 0; _x < image.width; ++_x) {
		for (int _y = 0; _y < image.height / 2; ++_y) {
			//swap the pixel with the corresponding pixel on the other side of the image
			for (int k = 0; k < 3; ++k) {
				unsigned char Vtemp = image(_x, _y, k);
				image(_x, _y, k) = image(_x, image.height - 1 - _y, k);
				image(_x, image.height - 1 - _y, k) = Vtemp;

			}

		}
	}
}

void RotateImage(Image &img, int degree) {
	int loops = degree / 90;
	//loop through each pixel in the image and rotate it by 90 degrees for the specified number of loops
	for (int k = 0;k < loops;k++) {

		Image newImg(img.height, img.width);

		for (int x = 0;x < img.width;x++) {
			//loop through each pixel in the image and set the corresponding pixel in the new image to the rotated position
			for (int y = 0;y < img.height;y++) {

				int newX = img.height - 1 - y;
				int newY = x;

				newImg(newX, newY, 0) = img(x, y, 0);
				newImg(newX, newY, 1) = img(x, y, 1);
				newImg(newX, newY, 2) = img(x, y, 2);
			}
		}
		img = newImg;
	}
}

void lighten_darken_fil(Image& img, char choice) {
	//loop through each pixel in the image and lighten or darken it based on the user's choice
	int val = 70;
	for (int i = 0;i < img.width;++i) {
		for (int j = 0;j < img.height;++j) {
			//loop through each color channel (RGB) and adjust the pixel value based on the user's choice
			for (int k = 0;k < 3;++k) {
				int newcolor=img(i,j,k);
				if (choice == 'L' or choice == 'l')
					newcolor =img(i,j,k) * 1.5;
				if (choice == 'D' or choice == 'd')
					newcolor = (img(i, j, k) * 0.5);
				if (newcolor > 255) newcolor = 255;
				if (newcolor < 0) newcolor = 0;
				img(i, j, k) = newcolor;
			}
		}
	}
}

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

void showMenu() {
	//Display the menu options to the user
	cout << "1.Load a new image" << endl;
	cout << "2.Grayscale" << endl;
	cout << "3.Black and White" << endl;
	cout << "4.Invert Image" << endl;
    cout << "5.Frame" << endl;
    cout << "6.Flip Image" << endl;
    cout << "7.Rotate" << endl;
    cout << "8.Darken or Lighten" << endl;
    cout << "9.Resize" << endl;
	cout << "10.Save the image" << endl;
	cout << "11.Exit" << endl;
	cout << "Choose an option: ";
}

bool isValidImage(string name) {
	//check if the file exists and has a valid extension
	ifstream file(name);

    if (!file.is_open()) {
		return false;
	}

	int dot = name.rfind('.');

	if (dot == -1) {
		return false;
	}

	string extension = name.substr(dot);

	if (extension == ".jpg" || extension == ".jpeg" ||
		extension == ".png" || extension == ".bmp") {
		return true;
	}

	return false;
}

bool isValidExtension(string name) {
	//check if the file has a valid extension
	int dot = name.rfind('.');

	if (dot == -1) {
		return false;
	}

	string extension = name.substr(dot);

	if (extension == ".jpg" || extension == ".jpeg" ||
		extension == ".png" || extension == ".bmp") {
		return true;
	}

	return false;
}

int main() { 
	string file;
//Prompt the user to enter a valid image file name until a valid one is provided
while (true) {
    cout << "Enter the image file name (with extension): ";
    if (!(cin >> file)) {
        cout << "No input available. Exiting." << endl;
        return 1;
    }

    if (isValidImage(file)) {
        break;
    }

    cout << "Invalid file. Please try again." << endl;
}
	//Create an Image object using the provided file name
	Image image(file);
	//Display the menu and process user choices until the user chooses to exit
	int choice;
	while (true) {
		showMenu();
		cin >> choice;
		if (choice == 11) {
			cout << "Do you want to save before exit? (y/n): ";
			char answer;
			cin >> answer;

			if (answer == 'y') {
				char saveAnswer;

				cout << "Save with the same name? (y/n): ";
				cin >> saveAnswer;

				if (saveAnswer == 'y') {
					image.saveImage(file);
				}
				else {
					string saveName;

					while (true) {
						cout << "Enter the new file name: ";
						cin >> saveName;

						if (isValidExtension(saveName)) {
							break;
						}

						cout << "Invalid extension. Please try again." << endl;
					}

					image.saveImage(saveName);
				}
			}
			break;
		}		
		//Process the user's choice and call the appropriate function
		else if (choice == 2){
			Grayscale(image);
		}

        else if (choice == 3) {
            BlackWhite(image);
        }	

        else if (choice == 4) {
            Invert(image);
        }	

        else if (choice == 5) {
			int frameChoice;
			//Prompt the user to choose between a simple or fancy frame
			cout << "1. Simple  2. Fancy: ";
			cin >> frameChoice;			
			//Prompt the user to enter the frame thickness and RGB values for the frame color
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

			if (frameChoice == 1) {
				AddFrame(image, thickness, r, g, b);

			}
			else if (frameChoice == 2) {
				AddFancyFrame(image, thickness, r, g, b);
			}
        }
		//Prompt the user to choose between horizontal or vertical flip
        else if (choice == 6) {
			cout << " 1. Horizontal  2. Vertical: ";
			int flipChoice;
			cin >> flipChoice;
			if (flipChoice == 1) {
				FlipHorizontal(image);
			}
			else if (flipChoice == 2) {
				FlipVertical(image);
			}
		}
		//Prompt the user to enter the degree of rotation and call the RotateImage function
        else if (choice == 7) {
            int degree;
            cout << "Enter the degree of rotation (90, 180, 270): ";
            cin >> degree;

            if (degree == 90 || degree == 180 || degree == 270) {
                RotateImage(image, degree);
            } else {
                cout << "Invalid degree. Please enter 90, 180, or 270." << endl;
            }
        }
		//Prompt the user to choose between lightening or darkening the image and call the lighten_darken_fil function
        else if (choice == 8) {
            char lightDarkChoice;
            cout << "Do you want to lighten or darken the image? (L/D): ";
            cin >> lightDarkChoice;

            if (lightDarkChoice == 'L' || lightDarkChoice == 'l' || lightDarkChoice == 'D' || lightDarkChoice == 'd') {
                lighten_darken_fil(image, lightDarkChoice);
            } else {
                cout << "Invalid choice. Please enter 'L' for lighten or 'D' for darken." << endl;
            }
        }
		//Prompt the user to enter the new width and height for resizing the image and call the Resize_Filter function
        else if (choice == 9) {
            int newWidth, newHeight;
            cout << "Enter the new width: ";
            cin >> newWidth;
            cout << "Enter the new height: ";
            cin >> newHeight;

            if (newWidth > 0 && newHeight > 0) {
                Resize_Filter(image, newHeight, newWidth);
            } else {
                cout << "Invalid dimensions. Width and height must be positive integers." << endl;
            }
        }    
		//Prompt the user to save the image with the same name or a new name and call the saveImage function
		else if (choice == 10) {
			char answer;

			cout << "Save with the same name? (y/n): ";
			cin >> answer;

			if (answer == 'y') {
				image.saveImage(file);
			}
			else {
				string saveName;

				while (true) {
					cout << "Enter the new file name: ";
					cin >> saveName;
					//Check if the new file name has a valid extension before saving the image
					if (isValidExtension(saveName)) {
                        image.saveImage(saveName);
						break;
					}

					cout << "Invalid extension. Please try again." << endl;
				}
				file = saveName;
			}
		}		
		//Prompt the user to load a new image and check if they want to save the current image first
		else if (choice == 1) {
			cout << "Do you want to save the current image first? (y/n): ";
			char answer;
			cin >> answer;

			if (answer == 'y') {
				string saveName;

				while (true) {
					cout << "Enter the file name to save: ";
					cin >> saveName;

					if (isValidExtension(saveName)) {
						break;
					}

					cout << "Invalid extension. Please try again." << endl;
				}

				image.saveImage(saveName);
				file = saveName;
			}

			string newName;
			//Prompt the user to enter a new image file name until a valid one is provided
			while (true) {
				cout << "Enter the new image file name: ";
				cin >> newName;

				if (isValidImage(newName)) {
					break;
				}

				cout << "Invalid image. Please try again." << endl;
			}
			//Load the new image and update the file name
			image.loadNewImage(newName);
			file = newName;
		}	
	}
	return 0;
}
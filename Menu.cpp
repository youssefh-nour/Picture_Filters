// #define _CRT_SECURE_NO_WARNINGS
// #include <iostream>
// #include "Image_Class.h"
// #include <fstream>

// using namespace std;

// void showMenu() {
// 	cout << "1.Load a new image" << endl;
// 	cout << "2.Grayscale" << endl;
// 	cout << "3.Black and White" << endl;
// 	cout << "4.Invert Image" << endl;
//     cout << "5.Frame" << endl;
//     cout << "6.Flip Image" << endl;
//     cout << "7.Rotate" << endl;
//     cout << "8.Darken or Lighten" << endl;
//     cout << "9.Resize" << endl;
// 	cout << "10.Save the image" << endl;
// 	cout << "11.Exit" << endl;
// 	cout << "Choose an option: ";
// }

// bool isValidImage(string name) {
// 	ifstream file(name);

//     if (!file.is_open()) {
// 		return false;
// 	}

// 	int dot = name.rfind('.');

// 	if (dot == -1) {
// 		return false;
// 	}

// 	string extension = name.substr(dot);

// 	if (extension == ".jpg" || extension == ".jpeg" ||
// 		extension == ".png" || extension == ".bmp") {
// 		return true;
// 	}

// 	return false;
// }

// bool isValidExtension(string name) {
// 	int dot = name.rfind('.');

// 	if (dot == -1) {
// 		return false;
// 	}

// 	string extension = name.substr(dot);

// 	if (extension == ".jpg" || extension == ".jpeg" ||
// 		extension == ".png" || extension == ".bmp") {
// 		return true;
// 	}

// 	return false;
// }

// int main() { 
// 	string file;

// 	while (true) {
// 		cout << "Enter the image file name (with extension): ";
// 		cin >> file;

// 		if (isValidImage(file)) {
// 			break;
// 		}

// 		cout << "Invalid file. Please try again." << endl;
// 	}

// 	Image image(file);

// 	int choice;
// 	while (true) {
// 		showMenu();
// 		cin >> choice;
// 		if (choice == 11) {
// 			cout << "Do you want to save before exit? (y/n): ";
// 			char answer;
// 			cin >> answer;

// 			if (answer == 'y') {
// 				char saveAnswer;

// 				cout << "Save with the same name? (y/n): ";
// 				cin >> saveAnswer;

// 				if (saveAnswer == 'y') {
// 					image.saveImage(file);
// 				}
// 				else {
// 					string saveName;

// 					while (true) {
// 						cout << "Enter the new file name: ";
// 						cin >> saveName;

// 						if (isValidExtension(saveName)) {
// 							break;
// 						}

// 						cout << "Invalid extension. Please try again." << endl;
// 					}

// 					image.saveImage(saveName);
// 				}
// 			}
// 			break;
// 		}		
		
// 		else if (choice == 2){
// 			Grayscale(image);
// 		}

//         else if (choice == 3) {
//             BlackWhite(image);
//         }	

//         else if (choice == 4) {
//             Invert(image);
//         }	

//         else if (choice == 5) {
// 			int frameChoice;
// 			cout << "1. Simple  2. Fancy: ";
// 			cin >> frameChoice;			
			
// 		    int thickness;
// 			int r;
// 			int g;
// 			int b;

// 			cout << " Enter Frame thickness: ";
// 			cin >> thickness;

// 			cout << " Enter red: ";
// 			cin >> r;

// 			cout << "Enter green: ";
// 			cin >> g;

// 			cout << "Enter blue: ";
// 			cin >> b;

// 			if (frameChoice == 1) {
// 				AddFrame(image, thickness, r, g, b);

// 			}
// 			else if (frameChoice == 2) {
// 				AddFancyFrame(image, thickness, r, g, b);
// 			}

//             else if (choice == 6) {
// 			cout << " 1. Horizontal  2. Vertical: ";
// 			int flipChoice;
// 			cin >> flipChoice;
// 			if (flipChoice == 1) {
// 				FlipHorizontal(image);
// 			}
// 			else if (flipChoice == 2) {
// 				FlipVertical(image);
// 			}
// 		}

//         else if (choice == 7) {
//             int degree;
//             cout << "Enter the degree of rotation (90, 180, 270): ";
//             cin >> degree;

//             if (degree == 90 || degree == 180 || degree == 270) {
//                 RotateImage(image, degree);
//             } else {
//                 cout << "Invalid degree. Please enter 90, 180, or 270." << endl;
//             }
//         }

//         else if (choice == 8) {
//             char lightDarkChoice;
//             cout << "Do you want to lighten or darken the image? (L/D): ";
//             cin >> lightDarkChoice;

//             if (lightDarkChoice == 'L' || lightDarkChoice == 'l' || lightDarkChoice == 'D' || lightDarkChoice == 'd') {
//                 lighten_darken_fil(image, lightDarkChoice);
//             } else {
//                 cout << "Invalid choice. Please enter 'L' for lighten or 'D' for darken." << endl;
//             }
//         }

//         else if (choice == 9) {
//             int newWidth, newHeight;
//             cout << "Enter the new width: ";
//             cin >> newWidth;
//             cout << "Enter the new height: ";
//             cin >> newHeight;

//             if (newWidth > 0 && newHeight > 0) {
//                 Resize_Filter(image, newHeight, newWidth);
//             } else {
//                 cout << "Invalid dimensions. Width and height must be positive integers." << endl;
//             }
//         }    

// 		else if (choice == 10) {
// 			char answer;

// 			cout << "Save with the same name? (y/n): ";
// 			cin >> answer;

// 			if (answer == 'y') {
// 				image.saveImage(file);
// 			}
// 			else {
// 				string saveName;

// 				while (true) {
// 					cout << "Enter the new file name: ";
// 					cin >> saveName;

// 					if (isValidExtension(saveName)) {
// 						break;
// 					}

// 					cout << "Invalid extension. Please try again." << endl;
// 				}

// 				image.saveImage(saveName);
// 				file = saveName;
// 			}
// 		}		

// 		}
// 		else if (choice == 1) {
// 			cout << "Do you want to save the current image first? (y/n): ";
// 			char answer;
// 			cin >> answer;

// 			if (answer == 'y') {
// 				string saveName;

// 				while (true) {
// 					cout << "Enter the file name to save: ";
// 					cin >> saveName;

// 					if (isValidExtension(saveName)) {
// 						break;
// 					}

// 					cout << "Invalid extension. Please try again." << endl;
// 				}

// 				image.saveImage(saveName);
// 				file = saveName;
// 			}

// 			string newName;

// 			while (true) {
// 				cout << "Enter the new image file name: ";
// 				cin >> newName;

// 				if (isValidImage(newName)) {
// 					break;
// 				}

// 				cout << "Invalid image. Please try again." << endl;
// 			}
// 			image.loadNewImage(newName);
// 			file = newName;
// 		}	
// 	}
// return 0;
// }
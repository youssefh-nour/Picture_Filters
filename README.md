# Picture Filters

A C++17 image-processing application built for **CS213 – Object-Oriented Programming, Assignment 1** (Faculty of Computing and Artificial Intelligence, Cairo University). Load a PNG, JPG or BMP image, apply any sequence of filters and transformations, and save the result.

The project has two parts:

- **Part 1:** a console program with a text menu for the core filters (`CS213_A1_Part1_*.cpp`).
- **Part 2:** a Qt Widgets desktop application (`ImageProcessorGui`) in which all filters are member functions of one `Image` class and are exposed through 21 buttons.

## Team

Name -	ID -	Lab
Habiba Mohamed Ahmed - 20250190	- 29,30
Youssef Hatem Nour -	20250868 - 32
Menna Allah Magdy	- 20250673 - 29,30
Salma Shams -	20250284 - 29,30

## Who did what

Name -	Filter
Habiba Mohamed Ahmed -	1, 5, 9, 13, 17
Youssef Hatem Nour -	4, 8, 12, 16, 18
Menna Allah Magdy -	3, 7, 11, 15, GUI
Salma Shams	- 2, 6, 10, 14, GUI

## Features

| Family | Filters |
|---|---|
| Colour | Grayscale, Black and white, Invert, Lighten / darken, Purple tint, Infrared, Natural sunlight, Old TV, Oil painting |
| Geometric | Flip horizontal, Flip vertical, Rotate (90 / 180 / 270), Crop, Resize, Skew, Merge |
| Spatial | Blur (summed-area table), Edge detection, Frame (simple and fancy) |

Image loading and saving (PNG, JPG, BMP, TGA output) is handled by [`stb_image`](https://github.com/nothings/stb) and `stb_image_write`, bundled in the repository.

## Requirements

- A C++17 compiler (GCC, Clang or MSVC)
- CMake 3.16 or newer
- Qt 5 or Qt 6 with the **Widgets** module

## Build and run

```bash
git clone <repository-url>
cd Picture_Filters
cmake -S . -B build
cmake --build build
./build/ImageProcessorGui        # on Windows: build\ImageProcessorGui.exe
```

Alternatively, open `CMakeLists.txt` in Qt Creator and press **Run**.

### Using the application

1. Click **load image** and choose a PNG, JPG or BMP file.
2. Click any filter button. Filters with parameters (rotate, crop, resize, skew, blur, frame, oil painting, lighten/darken) ask for them in a dialog.
3. Filters stack, so each one is applied to the result of the previous one.
4. Click **save image** and choose a name and format.

### Running a single filter on its own

Most filter files (for example `Blur.cpp`, `Resize_Filter.cpp`, `SkewImage.cpp`) contain a small `main()` that runs the filter on `luffy.jpg`. Compile one of them by itself, with `Image_Class.h` and the stb headers in the same folder:

```bash
g++ -std=c++17 -I. Blur.cpp -o blur_test
```

The Part 1 console program is built the same way:

```bash
g++ -std=c++17 -I. CS213_A1_Part1_*.cpp -o part1
```

## System breakdown

```
User ──► mainwindow.ui (buttons) ──► MainWindow slots (QFileDialog / QInputDialog)
                                          │ holds currentImage
                                          ▼
                              Image class (Image_Class.h)
                      pixel buffer · load / save · operator()(x, y, c)
                 ┌───────────────┼────────────────┐
           Colour filters   Geometric filters   Spatial filters
                                          │
                                          ▼
                          stb_image / stb_image_write ──► image files
```

`MainWindow::updateDisplayedImage()` writes the current image to `temp_gui_display.png` and shows it in the image label after every filter.

## Repository layout

| Path | Purpose |
|---|---|
| `main.cpp`, `mainwindow.h/.cpp`, `mainwindow.ui` | Qt application entry point, window logic and layout |
| `Image_Class.h` | `Image` class: pixel storage, I/O and all filters |
| `*.cpp` filter files (`Blur.cpp`, `Frame_Filter.cpp`, …) | Standalone development version of each filter with its own test `main()` |
| `CS213_A1_Part1_*.cpp` | Part 1 console program |
| `Menu.cpp` | Earlier console menu (commented out) |
| `stb_image.h`, `stb_image_write.h` | Third-party image I/O |
| `luffy.jpg`, `test1.jpg`, `test2.jpg` | Sample images |
| `CMakeLists.txt` | Build configuration for the GUI |

## Notes on the Blur filter

Blur builds a summed-area table per colour channel, so the sum over any square window is read from four table entries. The cost is therefore independent of the blur radius, instead of growing with radius². Windows are clamped at the image border, and the divisor is the number of pixels actually inside the window.

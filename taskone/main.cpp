#include "CImg.h"
#include <iostream>
#include <string>
#include <cstdlib> // for std::atoi (ask if allowed)

using namespace cimg_library;
using namespace std;

//#####################
// FUNCTION DEFINITIONS
//#####################

void help() {
    cout<< "Usage: of application " "<path to image_file> <command> <param>" << endl;
    cout << "Possible commands: "
            "--brightness <value>, "
            "--contrast <value>" << endl;
    cout<< "The application's possible commands are:" << endl;
    cout<<"--brightness <value> - the images brightness is increased by a value (of range 0-255) specified." << endl;
    cout<<"--contrast <value> - the images contrast is increased by a value (0-255) specified." << endl;

}
// Function to adjust brightness
void doBrightness(CImg<unsigned char> &image, int value) {
    cout << "Adjusting brightness by: " << value << endl;

    // goes through all pixels and adds brightness to each color channel
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < 3; c++) { // 0 = red, 1 = green, 2 = blue
                int newVal = image(x, y, c) + value;
                if (newVal > 255) newVal = 255; // max val must be 255
                if (newVal < 0) newVal = 0;
                image(x, y, c) = newVal;
            }
        }
    }
}

// simplified linear contrast adjustment
void doContrast(CImg<unsigned char> &image, float factor) {
    cout << "Adjusting contrast with factor: " << factor << endl;

    // Iterate over all pixels and adjust contrast
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < 3; c++) { // 0 = red, 1 = green, 2 = blue
                float newVal = 128 + factor * (image(x, y, c) - 128); // Linear contrast formula
                if (newVal > 255) newVal = 255; // Clamp values between 0 and 255
                if (newVal < 0) newVal = 0;
                image(x, y, c) = static_cast<unsigned char>(newVal);
            }
        }
    }
}

void doNegative(CImg<unsigned char> &image) {
    cout << "Creating a negative of image:" << endl;
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < 3; c++) {
                int newVal = 255 - image(x, y, c) ;
                if (newVal > 255) newVal = 255; // max val must be 255
                if (newVal < 0) newVal = 0;
                image(x, y, c) = newVal;
            }
        }
    }
}

void doHorizontalFlip(CImg<unsigned char> &image) {
    int width = image.width();
    int height = image.height();

    // Iterate over half the width, swapping pixels horizontally
    for (int x = 0; x < width / 2; x++) {
        for (int y = 0; y < height; y++) {
            for (int c = 0; c < 3; c++) { // Loop over color channels: 0 = red, 1 = green, 2 = blue
                // Swap the pixel at (x, y) with its horizontally mirrored pixel at (width - 1 - x, y)
                std::swap(image(x, y, c), image(width - 1 - x, y, c));
            }
        }
    }
}

void doVerticalFlip(CImg<unsigned char> &image) {
    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height / 2; y++) {
        for(int x = 0; x < width; x++) {
            for (int c = 0; c < 3; c++) {
                std::swap(image(x, y, c), image(x, height- 1 - y, c));
            }
        }
    }
}
void doDiagonalFlip(CImg<unsigned char> &image) {
    doHorizontalFlip(image);
    doVerticalFlip(image);
}
//##########################
// HERE THE MAIN PART STARTS
//##########################

int main(int argc, char* argv[]) {
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <path to image_file> <command> [param]" << endl;
        cout << "Commands: --brightness <value>, --contrast <value>, --negative, --hflip, --vflip, --dflip" << endl;
        return 1;
    }

    string inputImage = argv[1];  // the input image file
    //string outputImage = argv[2]; // the output image file
    string command = argv[2];    // the command (e.g., --brightness or --contrast

    // Load the image
    CImg<unsigned char> image(inputImage.c_str());

    // Apply the appropriate command
    if (command == "--brightness") {
        if (argc < 4) {
            cout << "Error: Missing parameter for brightness adjustment." << endl;
            return 1;
        }
        string param = argv[3]; // the parameter for the command (e.g., value to adjust
        int brightnessValue = atoi(param.c_str()); // Convert param to integer
        doBrightness(image, brightnessValue);
    }
    else if (command == "--contrast") {
        if (argc < 4) {
            cout << "Error: Missing parameter for contrast adjustment." << endl;
            return 1;
        }
        string param = argv[3]; // the parameter for the command (e.g., value to adjust
        float contrastFactor = atof(param.c_str()); // Convert param to float
        doContrast(image, contrastFactor);
    }
    else if(command == "--negative") {
        doNegative(image);
    }
    else if(command =="--hflip") {
        doHorizontalFlip(image);
    }
    else if(command =="--vflip") {
        doVerticalFlip(image);
    }
    else if (command == "--help") {
        help();
    }
    else if(command =="--dflip") {
        doDiagonalFlip(image);
    }
    else {
        cout << "Unknown command: " << command << endl;
        return 1;
    }

    // Save the modified image
    image.save_bmp("outcm.bmp");
    cout << "Modified image saved as 'out.bmp'" << endl;

    return 0;
}


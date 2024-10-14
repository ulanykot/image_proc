#include "CImg.h"
#include <iostream>
#include <string>
#include <cstdlib> // for std::atoi (ask if allowed)

using namespace cimg_library;
using namespace std;

//#####################
// FUNCTION DEFINITIONS
//#####################

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

//##########################
// HERE THE MAIN PART STARTS
//##########################

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <image_file> <command> <param>" << endl;
        cout << "Commands: --brightness <value>, --contrast <value>" << endl;
        return 1;
    }

    string imageFile = argv[1];  // The input image file
    string command = argv[2];    // The command (e.g., --brightness or --contrast)
    string param = argv[3];      // The parameter for the command (e.g., value to adjust)

    // Load the image
    CImg<unsigned char> image(imageFile.c_str());

    // Apply the appropriate command
    if (command == "--brightness") {
        int brightnessValue = atoi(param.c_str()); // Convert param to integer
        doBrightness(image, brightnessValue);
    }
    else if (command == "--contrast") {
        float contrastFactor = atof(param.c_str()); // Convert param to float
        doContrast(image, contrastFactor);
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


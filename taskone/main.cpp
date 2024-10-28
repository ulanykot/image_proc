#include "CImg.h"
#include <iostream>
#include <string>
#include <cstdlib> // for std::atoi (ask if allowed)
#include <vector>

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

// void doImageShrinking(CImg<unsigned char> &image, float factor) {
//     if (factor <= 0 || factor >= 1) {
//         cout << "Invalid factor for shrinking. Must be in range (0, 1)." << endl;
//         return;
//     }
//     int new_width = static_cast<int>(image.width() * factor);
//     int new_height = static_cast<int>(image.height() * factor);
//     image.resize(new_width, new_height, -100, -100, 5); // Use bicubic interpolation (method 5)
// }

void doImageShrinking(CImg<unsigned char> &image, float factor) {
    if (factor <= 0 || factor >= 1) {
        cout << "Invalid factor for shrinking. Must be in range (0, 1)." << endl;
        return;
    }

    int new_width = static_cast<int>(image.width() * factor);
    int new_height = static_cast<int>(image.height() * factor);

    const int channels = 3; // Amount of channels for RGB image

    CImg<unsigned char> resized_image(new_width, new_height, 1, channels, 0);

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int src_x = static_cast<int>(x / factor);
            int src_y = static_cast<int>(y / factor);

            for (int c = 0; c < channels; ++c) {
                resized_image(x, y, 0, c) = image(src_x, src_y, 0, c);
            }
        }
    }

    image = resized_image;
}

// void doImageEnlargement(CImg<unsigned char> &image, float factor) {
//     if (factor <= 1) {
//         cout << "Invalid factor for enlargement. Must be greater than 1." << endl;
//         return;
//     }
//     int new_width = static_cast<int>(image.width() * factor);
//     int new_height = static_cast<int>(image.height() * factor);
//     image.resize(new_width, new_height, -100, -100, 5); // Use bicubic interpolation (method 5)
// }

// void doImageEnlargement(CImg<unsigned char> &image, float factor) {
//     if (factor <= 1) {
//         cout << "Invalid factor for enlargement. Must be greater than 1." << endl;
//         return;
//     }
//
//     int new_width = static_cast<int>(image.width() * factor);
//     int new_height = static_cast<int>(image.height() * factor);
//
//     CImg<unsigned char> resized_image(new_width, new_height, 1, image.spectrum(), 0);
//
//     for (int y = 0; y < new_height; ++y) {
//         for (int x = 0; x < new_width; ++x) {
//             float gx = x / factor;
//             float gy = y / factor;
//
//             int gxi = static_cast<int>(gx);
//             int gyi = static_cast<int>(gy);
//
//             float dx = gx - gxi;
//             float dy = gy - gyi;
//
//             for (int c = 0; c < image.spectrum(); ++c) {
//                 unsigned char pixel_value =
//                     (1 - dx) * (1 - dy) * image(gxi, gyi, 0, c) +
//                     dx * (1 - dy) * image(gxi + 1, gyi, 0, c) +
//                     (1 - dx) * dy * image(gxi, gyi + 1, 0, c) +
//                     dx * dy * image(gxi + 1, gyi + 1, 0, c);
//
//                 resized_image(x, y, 0, c) = pixel_value;
//             }
//         }
//     }
//
//     image = resized_image;
// }

void doImageEnlargement(CImg<unsigned char> &image, float factor) {
    if (factor <= 1) {
        cout << "Invalid factor for enlargement. Must be greater than 1." << endl;
        return;
    }

    int new_width = static_cast<int>(image.width() * factor);
    int new_height = static_cast<int>(image.height() * factor);

    const int channels = 3; // Amount of channels for RGB image

    CImg<unsigned char> resized_image(new_width, new_height, 1, channels, 0);

    for (int y = 0; y < new_height; ++y) {
        for (int x = 0; x < new_width; ++x) {
            int nearest_x = static_cast<int>(x / factor);
            int nearest_y = static_cast<int>(y / factor);

            for (int c = 0; c < channels; ++c) {
                resized_image(x, y, 0, c) = image(nearest_x, nearest_y, 0, c);
            }
        }
    }

    image = resized_image;
}

void minFilter(CImg<unsigned char> &image, int filter_size) {
    int width = image.width();
    int height = image.height();
    int half_size = filter_size / 2;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int c = 0; c < 3; c++) { // Loop over color channels
                unsigned char min_value = 255;
                // Iterate over the filter window
                for (int i = -half_size; i <= half_size; i++) {
                    for (int j = -half_size; j <= half_size; j++) {
                        int new_x = x + i;
                        int new_y = y + j;
                        if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                            min_value = std::min(min_value, image(new_x, new_y, c));
                        }
                    }
                }
                image(x, y, c) = min_value;
            }
        }
    }
}

void maxFilter(CImg<unsigned char> &image, int filter_size) {
    int width = image.width();
    int height = image.height();
    int half_size = filter_size / 2;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int c = 0; c < 3; c++) { // Loop over color channels
                unsigned char max_value = 0;
                // Iterate over the filter window
                for (int i = -half_size; i <= half_size; i++) {
                    for (int j = -half_size; j <= half_size; j++) {
                        int new_x = x + i;
                        int new_y = y + j;
                        if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                            max_value = std::max(max_value, image(new_x, new_y, c));
                        }
                    }
                }
                image(x, y, c) = max_value;
            }
        }
    }
}

void medianFilter(CImg<unsigned char> &image, int filter_size) {
    int width = image.width();
    int height = image.height();
    int half_size = filter_size / 2;

    vector<unsigned char> neighborhood;

    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            for (int c = 0; c < 3; c++) { // Loop over color channels
                neighborhood.clear();
                // Collect neighborhood values
                for (int i = -half_size; i <= half_size; i++) {
                    for (int j = -half_size; j <= half_size; j++) {
                        int new_x = x + i;
                        int new_y = y + j;
                        if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
                            neighborhood.push_back(image(new_x, new_y, c));
                        }
                    }
                }
                // Find the median value
                std::sort(neighborhood.begin(), neighborhood.end());
                unsigned char median_value = neighborhood[neighborhood.size() / 2];
                image(x, y, c) = median_value;
            }
        }
    }
}

//##########################
// HERE THE MAIN PART STARTS
//##########################

int main(int argc, char* argv[]) {

    string inputImage = argv[1];  // the input image file
    //string outputImage = argv[2]; // the output image file
    string command = argv[2];    // the command (e.g., --brightness or --contrast
    if (argc < 3) {
        cout << "Usage: " << argv[0] << " <path to image_file> <command> [param]" << endl;
        cout << "Commands: --brightness <value>, --contrast <value>, --negative, --hflip" << endl;
        return 1;
    }

    // Load the image
    CImg<unsigned char> image((inputImage.data()));

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
    else if(command == "--help") {
        help();
    }
    else if(command =="--dflip") {
        doDiagonalFlip(image);
    }
    else if(command =="--shrink") {
        if (argc < 4) {
            cout << "Error: Missing parameter for shrinking image." << endl;
            return 1;
        }
        string param = argv[3];
        float shrinkFactor = atof(param.c_str()); // Convert param to float
        doImageShrinking(image, shrinkFactor);
    }
    else if(command =="--enlarge") {
        if (argc < 4) {
            cout << "Error: Missing parameter for enlarging image." << endl;
            return 1;
        }
        string param = argv[3];
        float enlargeFactor = atof(param.c_str()); // Convert param to float
        doImageEnlargement(image, enlargeFactor);
    }
    else if(command =="--min") {
        int filter_size = (argc >= 4) ? atoi(argv[3]) : 3; // default filter size is 3
        minFilter(image, filter_size);
    }
    else if(command =="--max") {
        int filter_size = (argc >= 4) ? atoi(argv[3]) : 3; // default filter size is 3
        maxFilter(image, filter_size);
    }
    else if(command =="--median") {
        int filter_size = (argc >= 4) ? atoi(argv[3]) : 3; // default filter size is 3
        medianFilter(image, filter_size);
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


#include "CImg.h"
#include <iostream>

#include "CommandLineInterface.h"

using namespace cimg_library;
using namespace std;
//
// //#####################
// // FUNCTION DEFINITIONS
// //#####################
//
// void help() {
//     cout<< "Usage: of application " "<path to image_file> <command> <param>" << endl;
//     cout << "Possible commands: "
//             "--brightness <value>, "
//             "--contrast <value>" << endl;
//     cout<< "The application's possible commands are:" << endl;
//     cout<<"--brightness <value> - the images brightness is increased by a value (of range 0-255) specified." << endl;
//     cout<<"--contrast <value> - the images contrast is increased by a value (0-255) specified." << endl;
//
// }
// // Function to adjust brightness
// void doBrightness(CImg<unsigned char> &image, int value) {
//     cout << "Adjusting brightness by: " << value << endl;
//
//     // goes through all pixels and adds brightness to each color channel
//     for (int x = 0; x < image.width(); x++) {
//         for (int y = 0; y < image.height(); y++) {
//             for (int c = 0; c < 3; c++) { // 0 = red, 1 = green, 2 = blue
//                 int newVal = image(x, y, c) + value;
//                 if (newVal > 255) newVal = 255; // max val must be 255
//                 if (newVal < 0) newVal = 0;
//                 image(x, y, c) = newVal;
//             }
//         }
//     }
// }
//
// // simplified linear contrast adjustment
// void doContrast(CImg<unsigned char> &image, float factor) {
//     cout << "Adjusting contrast with factor: " << factor << endl;
//
//     // Iterate over all pixels and adjust contrast
//     for (int x = 0; x < image.width(); x++) {
//         for (int y = 0; y < image.height(); y++) {
//             for (int c = 0; c < 3; c++) { // 0 = red, 1 = green, 2 = blue
//                 float newVal = 128 + factor * (image(x, y, c) - 128); // Linear contrast formula
//                 if (newVal > 255) newVal = 255; // Clamp values between 0 and 255
//                 if (newVal < 0) newVal = 0;
//                 image(x, y, c) = static_cast<unsigned char>(newVal);
//             }
//         }
//     }
// }
//
// void doNegative(CImg<unsigned char> &image) {
//     cout << "Creating a negative of image:" << endl;
//     for (int x = 0; x < image.width(); x++) {
//         for (int y = 0; y < image.height(); y++) {
//             for (int c = 0; c < 3; c++) {
//                 int newVal = 255 - image(x, y, c) ;
//                 if (newVal > 255) newVal = 255; // max val must be 255
//                 if (newVal < 0) newVal = 0;
//                 image(x, y, c) = newVal;
//             }
//         }
//     }
// }
//
// void doHorizontalFlip(CImg<unsigned char> &image) {
//     int width = image.width();
//     int height = image.height();
//
//     // Iterate over half the width, swapping pixels horizontally
//     for (int x = 0; x < width / 2; x++) {
//         for (int y = 0; y < height; y++) {
//             for (int c = 0; c < 3; c++) { // Loop over color channels: 0 = red, 1 = green, 2 = blue
//                 // Swap the pixel at (x, y) with its horizontally mirrored pixel at (width - 1 - x, y)
//                 std::swap(image(x, y, c), image(width - 1 - x, y, c));
//             }
//         }
//     }
// }
//
// void doVerticalFlip(CImg<unsigned char> &image) {
//     int width = image.width();
//     int height = image.height();
//
//     for (int y = 0; y < height / 2; y++) {
//         for(int x = 0; x < width; x++) {
//             for (int c = 0; c < 3; c++) {
//                 std::swap(image(x, y, c), image(x, height- 1 - y, c));
//             }
//         }
//     }
// }
//
// void doDiagonalFlip(CImg<unsigned char> &image) {
//     doHorizontalFlip(image);
//     doVerticalFlip(image);
// }
//
// void doImageShrinking(CImg<unsigned char> &image, float factor) {
//     if (factor <= 0 || factor >= 1) {
//         cout << "Invalid factor for shrinking. Must be in range (0, 1)." << endl;
//         return;
//     }
//     int new_width = static_cast<int>(image.width() * factor);
//     int new_height = static_cast<int>(image.height() * factor);
//     CImg<unsigned char> shrunkImage(new_width,new_height, 1, image.spectrum());
//
//     for (int x = 0; x < new_width; ++x) {
//         for (int y = 0; y < new_height; ++y) {
//             for (int c = 0; c < image.spectrum(); ++c) {
//                 int src_x = static_cast<int>(x / factor);
//                 int src_y = static_cast<int>(y / factor);
//                 shrunkImage(x, y, 0, c) = image(src_x, src_y, 0, c);
//             }
//         }
//     }
//     image = shrunkImage;
//
// }
//
// void doImageEnlargement(CImg<unsigned char> &image, float factor) {
//     if (factor <= 1) {
//         cout << "Invalid factor for enlargement. Must be greater than 1." << endl;
//         return;
//     }
//     int new_width = static_cast<int>(image.width() * factor);
//     int new_height = static_cast<int>(image.height() * factor);
//     CImg<unsigned char> enlargedImage(new_width,new_height, 1, image.spectrum());
//
//     for (int x = 0; x < new_width; x++) {
//         for (int y = 0; y < new_height; y++) {
//             for (int c = 0; c < image.spectrum(); c++) {
//                 int src_x = static_cast<int>(x / factor);
//                 int src_y = static_cast<int>(y / factor);
//                 enlargedImage(x, y, 0, c) = image(src_x, src_y, 0, c);
//             }
//         }
//     }
//     image = enlargedImage;
//
// }
//
// void minFilter(CImg<unsigned char>& image, int filter_size) {
//     if (filter_size % 2 == 0) {
//         throw std::invalid_argument("Filter size must be odd");
//     }
//
//     int width = image.width();
//     int height = image.height();
//     int half_size = filter_size / 2;
//     int windowArea = filter_size * filter_size;
//
//     CImg<unsigned char> filteredImage = image; // Temporary image to store results
//
//     for (int c = 0; c < image.spectrum(); ++c) { // Iterate over color channels
//         for (int x = half_size; x < width - half_size; ++x) {
//             for (int y = half_size; y < height - half_size; ++y) {
//                 int* window = new int[windowArea];
//                 int windowIndex = 0;
//
//                 // Collect neighborhood values
//                 for (int i = -half_size; i <= half_size; ++i) {
//                     for (int j = -half_size; j <= half_size; ++j) {
//                         int new_x = x + i;
//                         int new_y = y + j;
//                         window[windowIndex++] = image(new_x, new_y, 0, c);
//                     }
//                 }
//
//                 // Sort the window and find the minimum value
//                 std::sort(window, window + windowIndex);
//                 filteredImage(x, y, 0, c) = window[0]; // Minimum value
//
//                 delete[] window;
//             }
//         }
//     }
//
//     image = filteredImage;
// }
//
// void maxFilter(CImg<unsigned char>& image, int windowSize) {
//     if (windowSize % 2 == 0) {
//         throw std::invalid_argument("Window size must be odd");
//     }
//
//     CImg<unsigned char> filteredImage = image; // Temporary image for storing the result
//
//     int halfWindowSize = windowSize / 2;
//     int windowArea = windowSize * windowSize;
//
//     for (int c = 0; c < image.spectrum(); ++c) { // Iterate over each color channel
//         for (int x = halfWindowSize; x < image.width() - halfWindowSize; ++x) {
//             for (int y = halfWindowSize; y < image.height() - halfWindowSize; ++y) {
//                 int* window = new int[windowArea];
//                 int windowIndex = 0;
//
//                 // Collect neighborhood values
//                 for (int i = x - halfWindowSize; i <= x + halfWindowSize; ++i) {
//                     for (int j = y - halfWindowSize; j <= y + halfWindowSize; ++j) {
//                         window[windowIndex++] = image(i, j, 0, c);
//                     }
//                 }
//
//                 // Sort and find the maximum value
//                 std::sort(window, window + windowIndex);
//                 filteredImage(x, y, 0, c) = window[windowIndex - 1]; // Maximum value
//                 delete[] window;
//             }
//         }
//     }
//
//     image = filteredImage;
// }
//
//
// void medianFilter(CImg<unsigned char> &image, int filter_size) {
//     int width = image.width();
//     int height = image.height();
//     int half_size = filter_size / 2;
//
//     vector<unsigned char> neighborhood;
//
//     for (int x = 0; x < width; x++) {
//         for (int y = 0; y < height; y++) {
//             for (int c = 0; c < 3; c++) { // Loop over color channels
//                 neighborhood.clear();
//                 // Collect neighborhood values
//                 for (int i = -half_size; i <= half_size; i++) {
//                     for (int j = -half_size; j <= half_size; j++) {
//                         int new_x = x + i;
//                         int new_y = y + j;
//                         if (new_x >= 0 && new_x < width && new_y >= 0 && new_y < height) {
//                             neighborhood.push_back(image(new_x, new_y, c));
//                         }
//                     }
//                 }
//                 // Find the median value
//                 std::sort(neighborhood.begin(), neighborhood.end());
//                 unsigned char median_value = neighborhood[neighborhood.size() / 2];
//                 image(x, y, c) = median_value;
//             }
//         }
//     }
// }
//
// //##########################
// // HERE THE MAIN PART STARTS
// //##########################

int main(int argc, char* argv[]) {
    CommandLineInterface::parseCommand(argc, argv);
    return 0;
}


//
// Created by MSI on 29.10.2024.
//

#include "FilterOperations.h"

#include <stdexcept>
#include <vector>

void FilterOperations::minFilter(cimg_library::CImg<unsigned char>& image, int filter_size) {
    if (filter_size % 2 == 0 || filter_size < 0 ) {
        throw std::invalid_argument("Filter size must be odd and positive.");
    }

    int width = image.width();
    int height = image.height();
    int half_size = filter_size / 2;
    int windowArea = filter_size * filter_size;

    cimg_library::CImg<unsigned char> filteredImage = image; // Temporary image to store results

    for (int c = 0; c < image.spectrum(); ++c) { // go over color channels
        for (int x = half_size; x < width - half_size; ++x) {
            for (int y = half_size; y < height - half_size; ++y) {
                int* window = new int[windowArea];
                int windowIndex = 0;

                // Collect neighborhood values
                for (int i = -half_size; i <= half_size; ++i) {
                    for (int j = -half_size; j <= half_size; ++j) {
                        int new_x = x + i;
                        int new_y = y + j;
                        window[windowIndex++] = image(new_x, new_y, 0, c);
                    }
                }

                // Sort the window and find the minimum value
                std::sort(window, window + windowIndex);
                filteredImage(x, y, 0, c) = window[0]; // Minimum value

                delete[] window;
            }
        }
    }

    image = filteredImage;
}

void FilterOperations::maxFilter(cimg_library::CImg<unsigned char>& image, int filter_size) {
    if (filter_size % 2 == 0 || filter_size < 0 ) {
        throw std::invalid_argument("Filter size must be odd and positive.");
    }

    cimg_library::CImg<unsigned char> filteredImage = image; // Temporary image for storing the result

    int half_size = filter_size / 2;
    int windowArea = filter_size * filter_size;

    for (int c = 0; c < image.spectrum(); ++c) { // Iterate over each color channel
        for (int x = half_size; x < image.width() - half_size; ++x) {
            for (int y = half_size; y < image.height() - half_size; ++y) {
                int* window = new int[windowArea];
                int windowIndex = 0;

                // Collect neighborhood values
                for (int i = x - half_size; i <= x + half_size; ++i) {
                    for (int j = y - half_size; j <= y + half_size; ++j) {
                        window[windowIndex++] = image(i, j, 0, c);
                    }
                }

                // Sort and find the maximum value
                std::sort(window, window + windowIndex);
                filteredImage(x, y, 0, c) = window[windowIndex - 1]; // Maximum value
                delete[] window;
            }
        }
    }

    image = filteredImage;
}

void FilterOperations::medianFilter(cimg_library::CImg<unsigned char> &image, int filter_size) {
    if (filter_size % 2 == 0 || filter_size < 0 ) {
        throw std::invalid_argument("Filter size must be odd and positive.");
    }
    int width = image.width();
    int height = image.height();
    int half_size = filter_size / 2;

    std::vector<unsigned char> neighborhood;

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
bool isPowerOfTwo(int n)
{
    if (n == 0)
        return 0;
    while (n != 1) {
        if (n % 2 != 0)
            return 0;
        n = n / 2;
    }
    return 1;
}

void FilterOperations::rosenfeldOperator(cimg_library::CImg<unsigned char>& image, int power) {
     if(isPowerOfTwo(power) == false) {
        throw std::invalid_argument("Filter size must be a power of two.");
     }
    int width = image.width();
    cimg_library::CImg<unsigned char> filteredImage = image;

    cimg_forXYC(image,x,y,c) {
        int leftP = std::min(x,power); //caps the value if there would be no neighbouring pixels on the left side
        int rightP = std::min(width - x - 1, power); //caps the value if there would be no neighbouring pixels on right side
        float sum = 0;

        for (int i = 1; i <= leftP; i++) {
            sum -= image(x - i,y,c);
        }
        for (int j = 0; j < rightP; j++) {
            sum += image(x + j,y,c);
        }
        filteredImage(x,y,c) = static_cast<int>(std::clamp(sum / power,0.00f,255.00f));

    }
    image = filteredImage;
}


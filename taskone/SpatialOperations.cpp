//
// Created by MSI on 17.11.2024.
//

#include "SpatialOperations.h"

#include <stdexcept>
#include <vector>

bool isPowerOfTwo(int n)
{
    if (n == 0)
        return false;
    while (n != 1) {
        if (n % 2 != 0)
            return false;
        n = n / 2;
    }
    return true;
}

int SpatialOperations::h1[3][3] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };
int SpatialOperations::h2[3][3] = { {-1, -1, -1}, {-1, 9, -1}, {-1, -1, -1} };
int SpatialOperations::h3[3][3] = { {1, -2, 1}, {-2, 5, -2}, {1, -2, 1} };


void SpatialOperations::convolve(cimg_library::CImg<unsigned char>& image, int mask[3][3]) {
    int filter_size = 3;
    int half_size = filter_size / 2;

    cimg_library::CImg<unsigned char> filteredImage = image;

    for (int x = half_size; x < image.width() - half_size; x++) {
        for(int y = half_size; y < image.height() - half_size; y++) {
            for(int c = 0; c < image.spectrum(); c++) {
                if (x >= half_size && x < image.width() - half_size &&
                    y >= half_size && y < image.height() - half_size) {
                    int sum = 0;
                    for (int i = -half_size; i <= half_size; i++) {
                        for (int j = -half_size; j <= half_size; j++) {
                            sum += mask[i + 1][j + 1] * image(x + i, y + j, c);
                        }
                    }
                    filteredImage(x, y, c) = std::max(0, std::min(255, sum));
                }
                else {
                    // handling boarders g(p,q) = x(p,q)
                    filteredImage(x, y, c) = image(x, y, c);
                }
            }
        }
    }
    image = filteredImage;
}

void SpatialOperations::rosenfeldOperator(cimg_library::CImg<unsigned char>& image, int power) {
     if(isPowerOfTwo(power) == false || power < 0) {
        throw std::invalid_argument("Filter size must be a power of two.");
     }
    int width = image.width();
    cimg_library::CImg<unsigned char> filteredImage = image;

    cimg_forXYC(image,x,y,c) {
        const int leftP = std::min(x,power); //caps the value if there would be no neighbouring pixels on the left side
        const int rightP = std::min(width - x - 1, power); //caps the value if there would be no neighbouring pixels on right side
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

void SpatialOperations::edgeSharpening(cimg_library::CImg<unsigned char> &image, int mask) {
    //values 1 2 3 are used in the command line for choosing a mask
    if(mask == 1) {
        optimizedEdgeSharpening(image);
    }
    else if(mask == 2) {
        convolve(image,h2);
    }
    else if(mask == 3) {
        convolve(image,h3);
    }
}

void SpatialOperations::optimizedEdgeSharpening(cimg_library::CImg<unsigned char> &image) {
    static const int h1[3][3] = {
        { 0, -1,  0 },
        {-1,  5, -1 },
        { 0, -1,  0 }
    };

    const int width = image.width();
    const int height = image.height();
    const int spectrum = image.spectrum();

    cimg_library::CImg<unsigned char> filteredImage(width, height, 1, spectrum, 0);
    std::vector<int> rowBuffer[3] = {std::vector<int>(width * spectrum, 0),
                                     std::vector<int>(width * spectrum, 0),
                                     std::vector<int>(width * spectrum, 0)};

    for (int y = 1; y < height - 1; ++y) {
        for (int i = -1; i <= 1; ++i) {
            int srcRow = y + i;
            for (int x = 1; x < width - 1; ++x) {
                for (int c = 0; c < spectrum; ++c) {
                    rowBuffer[i + 1][x * spectrum + c] = image(x, srcRow, c);
                }
            }
        }

        for (int x = 1; x < width - 1; ++x) {
            for (int c = 0; c < spectrum; ++c) {
                int sum = 0;
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        sum += rowBuffer[i][(x + j - 1) * spectrum + c] * h1[i][j];
                    }
                }
                filteredImage(x, y, c) = std::clamp(sum, 0, 255);
            }
        }
    }
    image = filteredImage;
}

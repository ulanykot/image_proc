//
// Created by MSI on 19.01.2025.
//

#include "FrequencyFilters.h"

#include "FourierTransform.h"

void FrequencyFilters::lowPass(cimg_library::CImg<unsigned char> &image, int area) {
    complexVector2D imageVector = FourierTransform::performFFT(image);
    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    // Apply the low-pass filter
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int distSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distSquared > area * area) {
                imageVector[y][x] = 0; // Zero out frequencies outside the area
            }
        }
    }
    // Perform the inverse FFT to reconstruct the filtered image
    image = FourierTransform::performIFFT(imageVector);
}

void FrequencyFilters::highPass(cimg_library::CImg<unsigned char> &image, int area) {
}

void FrequencyFilters::bandPass(cimg_library::CImg<unsigned char> &image, int low, int high) {
}

void FrequencyFilters::bandCut(cimg_library::CImg<unsigned char> &image, int low, int high) {
}

void FrequencyFilters::highPassTwo(cimg_library::CImg<unsigned char> &image, int area) {
}

void FrequencyFilters::phaseMod() {
}

//
// Created by MSI on 19.01.2025.
//

#include "FrequencyFilters.h"

#include "FourierTransform.h"

complexVector2D FrequencyFilters::lowPass(complexVector2D imageVector, int area) {
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
    return imageVector;
}

void FrequencyFilters::doLowPass(cimg_library::CImg<unsigned char> &image, int area) {
    complexVector2D imageVector = FourierTransform::performFFT(image);
    complexVector2D lowPassVector = lowPass(imageVector,area);
    image = FourierTransform::performIFFT(lowPassVector);
}

void FrequencyFilters::highPass(cimg_library::CImg<unsigned char> &image, int area) {
    complexVector2D imageVector = FourierTransform::performFFT(image);
    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();

    // Create a copy of the frequency spectrum for low-pass filtering
    complexVector2D lowPassVector = lowPass(imageVector,area);

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            imageVector[y][x] -= lowPassVector[y][x]; // Subtract low-pass filtered frequencies
        }
    }
    image = FourierTransform::performIFFT(imageVector);
}

void FrequencyFilters::bandCut(cimg_library::CImg<unsigned char> &image, int center, int bandwidth) {
    complexVector2D frequencySpectrum = FourierTransform::performFFT(image);

    const size_t height = frequencySpectrum.size();
    const size_t width = frequencySpectrum[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int dx = x - centerX;
            int dy = y - centerY;
            double d = std::sqrt(dx * dx + dy * dy);

            if (d >= center - bandwidth / 2.0 && d <= center + bandwidth / 2.0) {
                frequencySpectrum[y][x] = 0; // cut
            }
        }
    }

    image = FourierTransform::performIFFT(frequencySpectrum);
}

void FrequencyFilters::bandPass(cimg_library::CImg<unsigned char> &image, int center, int bandwidth) {
    complexVector2D frequencySpectrum = FourierTransform::performFFT(image);

    const size_t height = frequencySpectrum.size();
    const size_t width = frequencySpectrum[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int dx = x - centerX;
            int dy = y - centerY;
            double d = std::sqrt(dx * dx + dy * dy);

            if (d >= center - bandwidth / 2.0 && d <= center + bandwidth / 2.0) {
                continue; //stays
            }
            frequencySpectrum[y][x] = 0; // other freq are zeroed out
        }
    }

    image = FourierTransform::performIFFT(frequencySpectrum);
}

void FrequencyFilters::highPassTwo(cimg_library::CImg<unsigned char> &image, int area) {
}

void FrequencyFilters::phaseMod() {
}

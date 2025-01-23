//
// Created by MSI on 19.01.2025.
//

#include "FrequencyFilters.h"

#include "FourierTransform.h"

void shiftVector(complexVector2D &spectrum) {
    const size_t rows = spectrum.size();
    const size_t cols = spectrum[0].size();

    complexVector2D unshifted(rows, std::vector<complex>(cols));

    for (size_t i = 0; i < rows / 2; ++i) {
        for (size_t j = 0; j < cols / 2; ++j) {
            unshifted[i][j] = spectrum[i + rows / 2][j + cols / 2];
            unshifted[i + rows / 2][j] = spectrum[i][j + cols / 2];
            unshifted[i][j + cols / 2] = spectrum[i + rows / 2][j];
            unshifted[i + rows / 2][j + cols / 2] = spectrum[i][j];
        }
    }

    spectrum = unshifted;
}

complexVector2D FrequencyFilters::lowPass(complexVector2D imageVector, int area) {
    shiftVector(imageVector);
    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    // Apply the low-pass filter
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int distSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distSquared > area * area) {
                imageVector[y][x] = complex(0, 0); // Zero out frequencies outside the area
            }
        }
    }
    shiftVector(imageVector);
    return imageVector;
}

void FrequencyFilters::doLowPass(cimg_library::CImg<unsigned char> &image, int area) {
    complexVector2D imageVector = FourierTransform::filterFFT(image);
    complexVector2D lowPassVector = lowPass(imageVector, area);
    //image = FourierTransform::visualizeSpectrum(imageVector);
    image = FourierTransform::performIFFT(lowPassVector);
}

void FrequencyFilters::highPass(cimg_library::CImg<unsigned char> &image, int area) {
    complexVector2D imageVector = FourierTransform::filterFFT(image);
    shiftVector(imageVector);
    complexVector2D lowPassVector = imageVector;

    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    // Apply the low-pass filter to the copy
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int distSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distSquared > area * area) {
                lowPassVector[y][x] = 0; // Zero out high frequencies for low-pass filter
            }
        }
    }

    // High-pass filter: HHP(u, v) = H(u, v) - HLP(u, v)
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            imageVector[y][x] -= lowPassVector[y][x]; // above function 1 - that
        }
    }
    shiftVector(imageVector);
    image = FourierTransform::performIFFT(imageVector);
}

void FrequencyFilters::bandCut(cimg_library::CImg<unsigned char> &image, int center, int bandwidth) {
    complexVector2D imageVector = FourierTransform::filterFFT(image);
    shiftVector(imageVector);

    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int dx = x - centerX;
            int dy = y - centerY;
            double d = std::sqrt(dx * dx + dy * dy);

            if (d >= center - bandwidth / 2.0 && d <= center + bandwidth / 2.0) {
                imageVector[y][x] = 0; // cut
            }
        }
    }
    shiftVector(imageVector);
    image = FourierTransform::performIFFT(imageVector);
}

void FrequencyFilters::bandPass(cimg_library::CImg<unsigned char> &image, int center, int bandwidth) {
    complexVector2D imageVector = FourierTransform::filterFFT(image);
    shiftVector(imageVector);
    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();
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
            imageVector[y][x] = 0; // other freq are zeroed out
        }
    }
    shiftVector(imageVector);
    image = FourierTransform::performIFFT(imageVector);
}

void FrequencyFilters::highPassTwo(cimg_library::CImg<unsigned char> &image, const cimg_library::CImg<unsigned char>& mask, int area) {
    complexVector2D imageVector = FourierTransform::filterFFT(image);
    shiftVector(imageVector);
    complexVector2D lowPassVector = imageVector;

    const size_t height = imageVector.size();
    const size_t width = imageVector[0].size();
    const size_t centerY = height / 2;
    const size_t centerX = width / 2;

    // Apply the low-pass filter to the copy
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            int distSquared = (x - centerX) * (x - centerX) + (y - centerY) * (y - centerY);
            if (distSquared > area * area) {
                lowPassVector[y][x] = 0; // Zero out high frequencies for low-pass filter
            }
        }
    }

    // High-pass filter: HHP(u, v) = H(u, v) - HLP(u, v)
    for (size_t y = 0; y < height; ++y) {
        for (size_t x = 0; x < width; ++x) {
            imageVector[y][x] -= lowPassVector[y][x]; // above function 1 - that
            if (mask(y, x) == 0) {
                imageVector[y][x] = 0;
            }
        }
    }
    shiftVector(imageVector);
    image = FourierTransform::performIFFT(imageVector);
}

void FrequencyFilters::phaseMod(cimg_library::CImg<unsigned char> &image, int k, int l) {
    complexVector2D imageVector = FourierTransform::filterFFT(image);
    shiftVector(imageVector);
    const size_t M = imageVector.size();
    const size_t N = imageVector[0].size();

    complexVector2D mask(M, std::vector<complex>(N));

    for (size_t y = 0; y < M; ++y) {
        for (size_t x = 0; x < N; ++x) {
            double phase = -((y * k * 2 * M_PI) / N) - ((x * l * 2 * M_PI) / M) + (k + l) * M_PI;
            mask[y][x] = std::polar(1.0, phase);
        }
    }

    for (size_t m = 0; m < M; ++m) {
        for (size_t n = 0; n < N; ++n) {
            imageVector[m][n] *= mask[m][n];
        }
    }
    shiftVector(imageVector);
    image = FourierTransform::performIFFT(imageVector);
}

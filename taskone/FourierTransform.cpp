//
// Created by MSI on 16.01.2025.
//

#include "FourierTransform.h"

//helper functions
complexVector2D FourierTransform::imageToComplexVector(cimg_library::CImg<unsigned char> &image) {
    int width = image.width();
    int height = image.height();
    complexVector2D result(height, std::vector<complex>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result[x][y] = complex(image(x, y), 0);
        }
    }
    return result;
}

cimg_library::CImg<unsigned char> FourierTransform::vectorToImage(complexVector2D &fourier) {
    return cimg_library::CImg<unsigned char>();
}

//1d transforms
void FourierTransform::DFT1D(complexVector &vector, bool inverse) {
    const int N = vector.size();
    int sign = 1;
    if (inverse) {
        sign = -sign;
    }
    const double angle = sign * 2 * M_PI / N;
    complexVector result(N);
    for (int k = 0; k < N; k++) {
        complex sum(0, 0);
        for (int n = 0; n < N; n++) {
            sum += vector[n] * std::polar(1.0, angle * k * n);
        }
        if (inverse) {
            sum /= N;
        }
        result[k] = sum;
    }
    vector = result;
}

//recursively
void FourierTransform::FFT1D(complexVector &vector, bool inverse) {
    const int N = vector.size();
    int sign = -1;
    if (inverse) {
        sign = -sign;
    }
    const double angle = sign * 2 * M_PI / N;
    if (N <= 1) return;

    complexVector low(N / 2);
    complexVector high(N / 2);
    for (int n = 0; n < N / 2; n++) {
        low[n] = vector[n] + vector[n + N / 2];
        high[n] = vector[n] - vector[n + N / 2] * std::polar(1.0, angle * n);
    }

    FFT1D(low, inverse);
    FFT1D(high, inverse);

    for (int k = 0; k < N / 2; k++) {
        vector[2 * k] = low[k];
        vector[ 2 * k + 1] = high[k];
    }
    if (inverse) {
        for (int i = 0; i < N; i++) {
            vector[i] /= 2; // divide by 2 at each level of recursion
        }
    }
}

//2d transforms
void FourierTransform::discreteFourier(cimg_library::CImg<unsigned char> &image, bool inverse) {
    complexVector2D imageVector = imageToComplexVector(image);
    for (auto& row : imageVector) {
        DFT1D(row, inverse);
    }
    for (size_t i = 0; i < imageVector[0].size(); i++) {
        complexVector column(imageVector.size());
        for (size_t j = 0; j < imageVector.size(); j++) {
            column[j] = imageVector[j][i];
        }
        DFT1D(column, inverse);
        for (size_t j = 0; j < imageVector.size(); j++) {
            imageVector[j][i] = column[j];
        }
    }
}

void FourierTransform::fastFourier(cimg_library::CImg<unsigned char> &image, bool inverse) {
    complexVector2D imageVector = imageToComplexVector(image);
    for (auto& row : imageVector) {
        FFT1D(row, inverse);
    }
    for (size_t i = 0; i < imageVector[0].size(); i++) {
        complexVector column(imageVector.size());
        for (size_t j = 0; j < imageVector.size(); j++) {
            column[j] = imageVector[j][i];
        }
        FFT1D(column, inverse);
        for (size_t j = 0; j < imageVector.size(); j++) {
            imageVector[j][i] = column[j];
        }
    }
}

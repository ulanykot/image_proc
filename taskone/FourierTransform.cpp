//
// Created by MSI on 16.01.2025.
//

#include "FourierTransform.h"

//helper functions
complexVector2D FourierTransform::imageToComplexVector(cimg_library::CImg<unsigned char> &image) {
    const size_t width = image.width();
    const size_t height = image.height();
    complexVector2D result(height, std::vector<complex>(width));
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result[x][y] = complex(image(x, y), 0);
        }
    }
    return result;
}

cimg_library::CImg<unsigned char> FourierTransform::vectorToImage(complexVector2D &fourier) {
    const size_t height = fourier.size();
    const size_t width = fourier[0].size();
    cimg_library::CImg<unsigned char> result(width, height, 1, 1, 0);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            result(x, y) = (unsigned char)std::abs(fourier[y][x].real());
        }
    }
    return result;
}

//1d transforms
void FourierTransform::DFT1D(complexVector &vector, bool inverse) {
    const size_t N = vector.size();
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
    const size_t N = vector.size();
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
complexVector2D FourierTransform::discreteFourier(cimg_library::CImg<unsigned char> &image, bool inverse) {
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
    return imageVector;
}

complexVector2D FourierTransform::fastFourier(cimg_library::CImg<unsigned char> &image, bool inverse) {
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
    return imageVector;
}

cimg_library::CImg<unsigned char> FourierTransform::visualizeSpectrum(complexVector2D &vector) {
    const size_t width = vector.size();
    const size_t height = vector[0].size();

    cimg_library::CImg<std::complex<float>> complex_img(width, height);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            complex_img(x, y) = vector[y][x];
        }
    }
    cimg_library::CImg<double> magnitude(width, height);

    cimg_forXY(complex_img, x, y) {
        magnitude(x, y) = std::abs(complex_img(x, y));
    }

    cimg_library::CImg<unsigned char> output_image(width, height);
    cimg_forXY(magnitude, x, y) {
        output_image(x, y) = static_cast<unsigned char>(magnitude(x, y) * 255.0 / magnitude.max());
    }
    return output_image;
    //no phase cuz grascale
}

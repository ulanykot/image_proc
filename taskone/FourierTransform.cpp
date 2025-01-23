//
// Created by MSI on 16.01.2025.
//

#include "FourierTransform.h"

#include "HelperFunctions.h"

//helper functions
complexVector2D FourierTransform::imageToComplexVector(cimg_library::CImg<unsigned char> &image) {
    image = HelperFunctions::convertToGrayscale(image);
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

complexVector2D FourierTransform::imageToComplexVector(const cimg_library::CImg<double>& image) {
    int width = image.width();
    int height = image.height();
    complexVector2D result(height, std::vector<complex>(width));
    cimg_forXY(image, x, y) {
        result[y][x] = complex(image(x, y, 0, 0), image(x, y, 1, 0));
    }
    return result;
}

cimg_library::CImg<unsigned char> FourierTransform::vectorToImage(complexVector2D &fourier) {
    const size_t height = fourier.size();
    const size_t width = fourier[0].size();
    cimg_library::CImg<unsigned char> result(width, height, 1, 1, 0);

    // Find the min and max real values in the vector
    double minVal = std::numeric_limits<double>::max();
    double maxVal = std::numeric_limits<double>::lowest();

    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            double realPart = fourier[x][y].real();
            minVal = std::min(minVal, realPart);
            maxVal = std::max(maxVal, realPart);
        }
    }

    // Normalize and clamp the values to [0, 255]
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            double normalized = 255.0 * (fourier[x][y].real() - minVal) / (maxVal - minVal);
            result(x, y) = static_cast<unsigned char>(std::clamp(normalized, 0.0, 255.0));
        }
    }

    return result;
}

//1d transforms
void FourierTransform::DFT1D(complexVector &vector, bool inverse) {
    const size_t N = vector.size();
    double sign = inverse ? 1 : -1;
    const double angle = sign * 2 * M_PI;
    complexVector result(N);
    for (int k = 0; k < N; k++) {
        complex sum(0, 0);
        for (int n = 0; n < N; n++) {
            sum += vector[n] * std::polar(1.0, angle * k * n / N);
        }
        if (inverse) {
            sum /= N;
        }
        result[k] = sum;
    }
    vector = result;
}

void FourierTransform::FFT1D(complexVector &vector, bool inverse) {
    const size_t N = vector.size();
    if (N <= 1) {
        return;
    }

    // Iteration FFT
    double sign = inverse ? 1 : -1;
    for (size_t len = N; len > 1; len >>= 1) {
        double angle = sign * 2 * M_PI / len;
        complex wlen(std::cos(angle), std::sin(angle));
        for (size_t i = 0; i < N; i += len) {
            complex w(1);
            for (size_t j = 0; j < len / 2; j++) {
                complex u = vector[i + j]; // Real part
                complex v = vector[i + j + len / 2]; // Imaginary part
                vector[i + j] = u + v;
                vector[i + j + len / 2] = (u - v) * w;
                w *= wlen;
            }
        }
    }
     // rBitValue value is the bit-reversed value of bitValue
    size_t rBitValue = 0;
    for (size_t bitValue = 1; bitValue < N; bitValue++) {
        size_t bit = N >> 1;
        while (rBitValue & bit) {
            rBitValue ^= bit;
            bit >>= 1;
        }
        rBitValue ^= bit;
        if (bitValue < rBitValue) {
            std::swap(vector[bitValue], vector[rBitValue]);
        }
    }

    if (inverse) {
        for(size_t i = 0; i < N; i++) {
            vector[i] /= N;
        }
    }
}

//2d transforms
complexVector2D FourierTransform::discreteFourier(complexVector2D& imageVector, bool inverse) {
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

complexVector2D FourierTransform::fastFourier(complexVector2D& imageVector, bool inverse) {
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
        magnitude(x, y) = log(1 + std::abs(complex_img(x, y)));
    }

    cimg_library::CImg<unsigned char> output_image(width, height);
    cimg_forXY(magnitude, x, y) {
        output_image(x, y) = static_cast<unsigned char>(magnitude(x, y) * 255.0 / magnitude.max());
    }
    output_image.shift(width / 2, height / 2, 0, 0, 2);
    return output_image;
}

complexVector2D FourierTransform::performDFT(cimg_library::CImg<unsigned char> &image) {
    complexVector2D imageVector = imageToComplexVector(image);
    discreteFourier(imageVector, false);
    image = visualizeSpectrum(imageVector);
    return imageVector;
}

cimg_library::CImg<unsigned char> FourierTransform::performIDFT(complexVector2D& vector) {
    discreteFourier(vector, true); // after this input is only real part
    cimg_library::CImg<unsigned char> result = vectorToImage(vector);
    return result;
}

complexVector2D FourierTransform::performFFT(cimg_library::CImg<unsigned char> &image) {
    complexVector2D imageVector = imageToComplexVector(image);
    fastFourier(imageVector, false);
    image = visualizeSpectrum(imageVector);
    return imageVector;
}

cimg_library::CImg<unsigned char> FourierTransform::performIFFT(complexVector2D& vector) {
    fastFourier(vector, true); // after this input is only real part
    cimg_library::CImg<unsigned char> result = vectorToImage(vector);
    return result;
}

complexVector2D FourierTransform::filterFFT(cimg_library::CImg<unsigned char> &image) {
    complexVector2D imageVector = imageToComplexVector(image);
    fastFourier(imageVector, false);
    return imageVector;
}

complexVector2D FourierTransform::filterDFT(cimg_library::CImg<unsigned char> &image) {
    complexVector2D imageVector = imageToComplexVector(image);
    fastFourier(imageVector, false);
    return imageVector;
}

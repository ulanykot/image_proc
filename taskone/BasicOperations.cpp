//
// Created by MSI on 29.10.2024.
//

#include "BasicOperations.h"

#include <stdexcept>

// Function to adjust brightness
void BasicOperations::doBrightness(cimg_library::CImg<unsigned char> &image, int value) {

    // goes through all pixels and adds brightness to each color channel
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                int newVal = std::max(0, std::min(255, image(x, y, c) + value));
                image(x, y, c) = newVal;
            }
        }
    }
}

// simplified linear contrast adjustment
void BasicOperations::doContrast(cimg_library::CImg<unsigned char> &image, float factor) {

    // Iterate over all pixels and adjust contrast
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                int newVal = std::max(0, std::min(255, static_cast<int>((128 + factor * (image(x, y, c) - 128)))));
                image(x, y, c) = static_cast<unsigned char>(newVal);
            }
        }
    }
}

void BasicOperations::doNegative(cimg_library::CImg<unsigned char> &image) {
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                int newVal = std::max(0, std::min(255, 255 - image(x, y, c)));
                image(x, y, c) = newVal;
            }
        }
    }
}

void BasicOperations::doHorizontalFlip(cimg_library::CImg<unsigned char> &image) {
    int width = image.width();
    int height = image.height();

    // Iterate over half the width, swapping pixels horizontally
    for (int x = 0; x < width / 2; x++) {
        for (int y = 0; y < height; y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                // Swap the pixel at (x, y) with its horizontally mirrored pixel at (width - 1 - x, y)
                std::swap(image(x, y, c), image(width - 1 - x, y, c));
            }
        }
    }
}

void BasicOperations::doVerticalFlip(cimg_library::CImg<unsigned char> &image) {
    int width = image.width();
    int height = image.height();

    for (int y = 0; y < height / 2; y++) {
        for(int x = 0; x < width; x++) {
            for (int c = 0; c < image.spectrum(); c++) {
                std::swap(image(x, y, c), image(x, height- 1 - y, c));
            }
        }
    }
}

void BasicOperations::doDiagonalFlip(cimg_library::CImg<unsigned char> &image) {
    doHorizontalFlip(image);
    doVerticalFlip(image);
}

void BasicOperations::doImageShrinking(cimg_library::CImg<unsigned char> &image, float factor) {
    if (factor <= 0 || factor >= 1) {
        throw std::invalid_argument("Factor of shrinking size must be between the range 0-1.");
    }
    int new_width = static_cast<int>(image.width() * factor);
    int new_height = static_cast<int>(image.height() * factor);
    cimg_library::CImg<unsigned char> shrunkImage(new_width,new_height, 1, image.spectrum());

    for (int x = 0; x < new_width; ++x) {
        for (int y = 0; y < new_height; ++y) {
            for (int c = 0; c < image.spectrum(); ++c) {
                int src_x = static_cast<int>(x / factor);
                int src_y = static_cast<int>(y / factor);
                shrunkImage(x, y, 0, c) = image(src_x, src_y, 0, c);
            }
        }
    }
    image = shrunkImage;

}

void BasicOperations::doImageEnlargement(cimg_library::CImg<unsigned char> &image, float factor) {
    if (factor <= 1) {
        throw std::invalid_argument("Factor of enlargement size must be larger than 1.");
    }
    int new_width = static_cast<int>(image.width() * factor);
    int new_height = static_cast<int>(image.height() * factor);
    cimg_library::CImg<unsigned char> enlargedImage(new_width,new_height, 1, image.spectrum());

    for (int x = 0; x < new_width; x++) {
        for (int y = 0; y < new_height; y++) {
            for (int c = 0; c < image.spectrum(); c++) {
                int src_x = static_cast<int>(x / factor);
                int src_y = static_cast<int>(y / factor);
                enlargedImage(x, y, 0, c) = image(src_x, src_y, 0, c);
            }
        }
    }
    image = enlargedImage;

}

//
// Created by MSI on 11.12.2024.
//

#include "HelperFunctions.h"

cimg_library::CImg<unsigned char> HelperFunctions::convertToGrayscale(const cimg_library::CImg<unsigned char> &image) {
    if (image.spectrum() == 1) {
        return image;
    }

    cimg_library::CImg<unsigned char> grayscaleImage(image.width(), image.height(), 1, 1); // this works because the image is already only 0 255 methinks
    cimg_forXY(image, x, y) {
        grayscaleImage(x, y) = (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
    }
    return grayscaleImage;
}

cimg_library::CImg<unsigned char> binarizeImage(const cimg_library::CImg<unsigned char> &image,
                                                unsigned char threshold = 128) {
    cimg_library::CImg<unsigned char> binaryImage(image.width(), image.height(), 1, 1);
    cimg_forXY(image, x, y) {
        binaryImage(x, y) = (image(x, y) > threshold) ? 255 : 0; //only 255 and 0
    }
    return binaryImage;
}

cimg_library::CImg<unsigned char> ensureSingleChannel(const cimg_library::CImg<unsigned char> &image) {
    if (image.spectrum() == 1) {
        return image;
    }
    return image.get_channel(0);
}

cimg_library::CImg<unsigned char> HelperFunctions::preprocessBinaryImage(const cimg_library::CImg<unsigned char> &image) {
    // converts to grayscale
    cimg_library::CImg<unsigned char> grayscaleImage = convertToGrayscale(image);

    // converts grayscale to binary
    cimg_library::CImg<unsigned char> binaryImage = binarizeImage(grayscaleImage);

    // ensure there's only one channel
    return ensureSingleChannel(binaryImage);
}


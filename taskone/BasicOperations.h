//
// Created by MSI on 29.10.2024.
//

#ifndef BASICOPERATIONS_H
#define BASICOPERATIONS_H
#include "CImg.h"


class BasicOperations {
public:
    static void doBrightness(cimg_library::CImg<unsigned char>& image, int value);
    static void doContrast(cimg_library::CImg<unsigned char>& image, float factor);
    static void doNegative(cimg_library::CImg<unsigned char>& image);
    static void doHorizontalFlip(cimg_library::CImg<unsigned char>& image);
    static void doVerticalFlip(cimg_library::CImg<unsigned char>& image);
    static void doDiagonalFlip(cimg_library::CImg<unsigned char>& image);
    static void doImageShrinking(cimg_library::CImg<unsigned char>& image, float factor);
    static void doImageEnlargement(cimg_library::CImg<unsigned char>& image, float factor);
};



#endif //BASICOPERATIONS_H

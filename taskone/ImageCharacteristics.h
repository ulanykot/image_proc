//
// Created by MSI on 12.11.2024.
//

#ifndef IMAGECHARACTERISTICS_H
#define IMAGECHARACTERISTICS_H
#include "CImg.h"


class ImageCharacteristics {
public:
    static double mean(cimg_library::CImg<unsigned char> image);
    static double variance(cimg_library::CImg<unsigned char> image);
    static double standardDeviation(cimg_library::CImg<unsigned char> image);
    static double variationCoefficient(cimg_library::CImg<unsigned char> image);
    static double asymmetryCoefficient(cimg_library::CImg<unsigned char> image);
    static double flatteningCoefficient(cimg_library::CImg<unsigned char> image);
    static double variationCoefficient2(cimg_library::CImg<unsigned char> image);
    static double informationSourceEntropy(cimg_library::CImg<unsigned char> image);
};



#endif //IMAGECHARACTERISTICS_H

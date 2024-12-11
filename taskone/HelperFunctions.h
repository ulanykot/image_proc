//
// Created by MSI on 11.12.2024.
//

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H
#include "CImg.h"


class HelperFunctions {
public:
    static cimg_library::CImg<unsigned char> convertToGrayscale(const cimg_library::CImg<unsigned char> &image);

    static cimg_library::CImg<unsigned char> preprocessBinaryImage(const cimg_library::CImg<unsigned char> &image);
};



#endif //HELPERFUNCTIONS_H

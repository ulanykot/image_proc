//
// Created by MSI on 27.11.2024.
//

#ifndef MORPHOLOGICALBASIC_H
#define MORPHOLOGICALBASIC_H
#include <array>

#include "CImg.h"


class MorphologicalBasic {
public:
    static std::array<std::array<int, 3>, 3> one;
    static std::array<std::array<int, 3>, 3> two;
    static std::array<std::array<int, 3>, 3> three;
    static std::array<std::array<int, 3>, 3> four;
    static std::array<std::array<int, 3>, 3> five;
    static std::array<std::array<int, 3>, 3> six;
    static std::array<std::array<int, 3>, 3> seven;
    static std::array<std::array<int, 3>, 3> eight;
    static std::array<std::array<int, 3>, 3> nine;
    static std::array<std::array<int, 3>, 3> ten;
    //HMT


    static void dilation(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static void erosion(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static void opening(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static void closing(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
};



#endif //MORPHOLOGICALBASIC_H

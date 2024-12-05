//
// Created by MSI on 27.11.2024.
//

#ifndef MORPHOLOGICALBASIC_H
#define MORPHOLOGICALBASIC_H
#include <array>

#include "CImg.h"


class MorphologicalBasic {
public:
#pragma region StructuringElements
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
    static std::array<std::array<int,3>, 3> eleven_left;
    static std::array<std::array<int, 3>, 3> eleven_top;
    static std::array<std::array<int, 3>, 3> eleven_right;
    static std::array<std::array<int, 3>, 3> eleven_bottom;

    static std::array<std::array<int, 3>, 3> twelve_three_bottom;
    static std::array<std::array<int, 3>, 3> twelve_square_left_bottom;
    static std::array<std::array<int, 3>, 3> twelve_three_left;
    static std::array<std::array<int, 3>, 3> twelve_square_left_top;

    static std::array<std::array<int, 3>, 3> twelve_three_top;
    static std::array<std::array<int, 3>, 3> twelve_square_right_top;
    static std::array<std::array<int, 3>, 3> twelve_three_right;
    static std::array<std::array<int, 3>, 3> twelve_square_right_bottom;
#pragma endregion

    static bool isInRange(const cimg_library::CImg<unsigned char> &image, int x, int y);

    static void dilation(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static void erosion(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static void opening(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static void closing(cimg_library::CImg<unsigned char>& image, const std::array<std::array<int,3>,3> &se);
    static cimg_library::CImg<unsigned char> hitOrMiss(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int, 3>, 3> &se);
    static void thinning(cimg_library::CImg<unsigned char>& image);

    static void doOpening(cimg_library::CImg<unsigned char> &image, int se);
    static void doClosing(cimg_library::CImg<unsigned char> &image, int se);
    static void doDilation(cimg_library::CImg<unsigned char> &image, int se);
    static void doErosion(cimg_library::CImg<unsigned char> &image, int se);
    static cimg_library::CImg<unsigned char> doHMT(cimg_library::CImg<unsigned char> &image, int se);


    static std::array<std::array<int, 3>, 3> assignNumberToStructuringElement(int se);
    static std::array<std::array<int, 3>, 3> assignNumberToSEHMT(int se);

};



#endif //MORPHOLOGICALBASIC_H

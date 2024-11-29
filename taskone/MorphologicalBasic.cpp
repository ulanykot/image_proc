//
// Created by MSI on 27.11.2024.
//

#include "MorphologicalBasic.h"

#include <iostream>
#include <ostream>

std::array<std::array<int, 3>, 3> MorphologicalBasic::one = {{{0,0,0}, {0,1,0}, {0,1,0}}}; //certainly good
std::array<std::array<int, 3>, 3> MorphologicalBasic::two = {{{0,0,0}, {0,1,1}, {0,0,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::three = {{{1,1,1}, {1,1,1}, {1,1,1}}}; //good
std::array<std::array<int, 3>, 3> MorphologicalBasic::four = {{{0,1,0}, {1,1,1}, {0,1,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::five = {{{0,0,0}, {0,1,1}, {0,1,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::six = {{{0,0,0}, {0,0,1}, {0,1,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::seven = {{{0,1,0}, {0,1,0}, {0,1,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::eight = {{{0,1,0}, {0,0,0}, {0,1,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::nine = {{{0,1,1}, {0,1,0}, {0,0,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::ten = {{{0,0,0}, {1,1,0}, {1,0,0}}};

void MorphologicalBasic::dilation(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int,3>,3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;

    for (int y = 0; y < filteredImage.height(); y++) {
        for (int x = 0; x < filteredImage.width(); x++)
            for (int c = 0; c < image.spectrum(); c++) {
                if (image(x,y) == 255) {
                    for (int i = 0; i < se.size(); i++) {
                        for (int j = 0; j < se[i].size(); j++)
                            if(se[i][j] == 1) {
                                int new_x = x + (i - 1); // se[1][1] is the middle value that is why -1 here and
                                int new_y = y + (j - 1); // here -1 too

                                if (new_x >= 0 && new_x < image.width() && new_y >= 0 && new_y < image.height()) {
                                    filteredImage(new_x, new_y,0,c) = 255;
                                }
                            }
                    }
                }
            }
    }
    image = filteredImage;
}

void MorphologicalBasic::erosion(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int, 3>, 3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;

    for (int y = 0; y < filteredImage.height(); y++) {
        for (int x = 0; x < filteredImage.width(); x++)
            for (int c = 0; c < image.spectrum(); c++) {
                if (image(x,y) == 255) {
                    for (int i = 0; i < se.size(); i++) {
                        for (int j = 0; j < se[i].size(); j++)
                            if(se[i][j] == 1) {
                                int new_x = x + (i - 1); // se[1][1] is the middle value that is why -1 here and
                                int new_y = y + (j - 1); // here -1 too

                                if (new_x < 0 && new_x >= image.width() && new_y < 0 && new_y >= image.height() || image(new_x,new_y) == 0) {
                                    filteredImage(x, y,0,c) = 0;
                                }
                            }
                    }
                }
            }
    }
    image = filteredImage;
}

void MorphologicalBasic::opening(cimg_library::CImg<unsigned char> &image,
    const std::array<std::array<int, 3>, 3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;
    erosion(filteredImage,se);
    dilation(filteredImage,se);
    image = filteredImage;
}

void MorphologicalBasic::closing(cimg_library::CImg<unsigned char> &image,
    const std::array<std::array<int, 3>, 3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;
    dilation(filteredImage,se);
    erosion(filteredImage,se);
    image = filteredImage;
}

static std::array<std::array<int, 3>, 3> assignNumberToStructuingElement(int se) {
    switch (se) {
        case 1:
            return MorphologicalBasic::one;
        case 2:
            return MorphologicalBasic::two;
        case 3:
            return MorphologicalBasic::three;
        case 4:
            return MorphologicalBasic::four;
        case 5:
            return MorphologicalBasic::five;
        case 6:
            return MorphologicalBasic::six;
        case 7:
            return MorphologicalBasic::seven;
        case 8:
            return MorphologicalBasic::eight;
        case 9:
            return MorphologicalBasic::nine;
        case 10:
            return MorphologicalBasic::ten;
    }
    return MorphologicalBasic::one;
}

void MorphologicalBasic::doOpening(cimg_library::CImg<unsigned char> &image, int se) {
    opening(image,assignNumberToStructuingElement(se));

}
void MorphologicalBasic::doClosing(cimg_library::CImg<unsigned char> &image, int se) {
    closing(image,assignNumberToStructuingElement(se));
}
void MorphologicalBasic::doDilation(cimg_library::CImg<unsigned char> &image, int se) {
    dilation(image,assignNumberToStructuingElement(se));
}
void MorphologicalBasic::doErosion(cimg_library::CImg<unsigned char> &image, int se) {
    erosion(image,assignNumberToStructuingElement(se));
}
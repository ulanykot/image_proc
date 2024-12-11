//
// Created by MSI on 27.11.2024.
//

#include "MorphologicalBasic.h"

#include <iostream>
#include <ostream>

#pragma region StructuringElements
std::array<std::array<int, 3>, 3> MorphologicalBasic::one = {{{0,0,0}, {0,1,0}, {0,1,0}}}; //right block
std::array<std::array<int, 3>, 3> MorphologicalBasic::two = {{{0,0,0}, {0,1,1}, {0,0,0}}}; //bottom block
std::array<std::array<int, 3>, 3> MorphologicalBasic::three = {{{1,1,1}, {1,1,1}, {1,1,1}}}; //square
std::array<std::array<int, 3>, 3> MorphologicalBasic::four = {{{0,1,0}, {1,1,1}, {0,1,0}}}; //cross
std::array<std::array<int, 3>, 3> MorphologicalBasic::five = {{{0,0,0}, {0,1,1}, {0,1,0}}}; //dziubek
std::array<std::array<int, 3>, 3> MorphologicalBasic::six = {{{0,0,0}, {0,0,1}, {0,1,0}}}; //dziubek no middle
std::array<std::array<int, 3>, 3> MorphologicalBasic::seven = {{{0,1,0}, {0,1,0}, {0,1,0}}}; //stripe
std::array<std::array<int, 3>, 3> MorphologicalBasic::eight = {{{0,1,0}, {0,0,0}, {0,1,0}}}; //stripe no middle
std::array<std::array<int, 3>, 3> MorphologicalBasic::nine = {{{0,1,1}, {0,1,0}, {0,0,0}}}; //dziubek middle po prawo
std::array<std::array<int, 3>, 3> MorphologicalBasic::ten = {{{0,0,0}, {1,1,0}, {1,0,0}}}; //dziubek middle na dole

//HMT where 2 is the inactive part
std::array<std::array<int,3>, 3> MorphologicalBasic::eleven_left = {{{1,1,1}, {2,0,2}, {2,2,2}}}; //pasek po lewo, srodek wylaczony
std::array<std::array<int, 3>, 3> MorphologicalBasic::eleven_top = {{{1,2,2}, {1,0,2}, {1,2,2}}}; //pasek od gory, srodek wylaczony
std::array<std::array<int, 3>, 3> MorphologicalBasic::eleven_right = {{{2,2,2}, {2,0,2}, {1,1,1}}}; //pasek od prawej, srodek wylaczony
std::array<std::array<int, 3>, 3> MorphologicalBasic::eleven_bottom = {{{2,2,1}, {2,0,1}, {2,2,1}}};//pasek od dolu, srodek wylaczony

std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_three_bottom = {{{0,2,1}, {0,1,1}, {0,2,1}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_square_left_bottom = {{{2,1,1}, {0,1,1}, {0,0,2}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_three_left = {{{1,1,1}, {2,1,2}, {0,0,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_square_left_top = {{{1,1,2}, {1,1,0}, {2,0,0}}};

std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_three_top = {{{1,2,0}, {1,1,0}, {1,2,0}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_square_right_top = {{{2,0,0}, {1,1,0}, {1,1,2}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_three_right = {{{0,0,0}, {2,1,2}, {1,1,1}}};
std::array<std::array<int, 3>, 3> MorphologicalBasic::twelve_square_right_bottom {{{0,0,2}, {0,1,1}, {2,1,1}}};
#pragma endregion
#pragma region helper functions

static std::array<std::array<int, 3>, 3> assignNumberToStructuringElement(int se) {
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
        default:
            return MorphologicalBasic::one;
    }
}

static std::array<std::array<int, 3>, 3> assignNumberToSEHMT(int se) {
    switch (se) {
        case 1:
            return MorphologicalBasic::eleven_left;
        case 2:
            return MorphologicalBasic::eleven_top;
        case 3:
            return MorphologicalBasic::eleven_right;
        case 4:
            return MorphologicalBasic::eleven_bottom;
        case 5:
            return MorphologicalBasic::twelve_three_bottom;
        case 6:
            return MorphologicalBasic::twelve_square_left_bottom;
        case 7:
            return MorphologicalBasic::twelve_three_left;
        case 8:
            return MorphologicalBasic::twelve_square_left_top;
        case 9:
            return MorphologicalBasic::twelve_three_top;
        case 10:
            return MorphologicalBasic::twelve_square_right_top;
        case 11:
            return MorphologicalBasic::twelve_three_right;
        case 12:
            return MorphologicalBasic::twelve_square_right_bottom;
        default:
            return MorphologicalBasic::one;
    }
}

static std::array<std::array<int, 3>, 3> assignNumberToSEThinning(int se) {
    switch (se) {
        case 1:
            return MorphologicalBasic::twelve_three_bottom;
        case 2:
            return MorphologicalBasic::twelve_square_left_bottom;
        case 3:
            return MorphologicalBasic::twelve_three_left;
        case 4:
            return MorphologicalBasic::twelve_square_left_top;
        case 5:
            return MorphologicalBasic::twelve_three_top;
        case 6:
            return MorphologicalBasic::twelve_square_right_top;
        case 7:
            return MorphologicalBasic::twelve_three_right;
        case 8:
            return MorphologicalBasic::twelve_square_right_bottom;
        default:
            std::cerr << "Invalid se" << std::endl;
    }
}

bool imagesAreEqual(const cimg_library::CImg<unsigned char> &image1, const cimg_library::CImg<unsigned char> &image2) {
    cimg_forXY(image1, x, y) {
        if (image1(x, y) != image2(x, y)) {
            return false;
        }
    }
    return true;
}

#pragma endregion

void MorphologicalBasic::dilation(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int,3>,3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;

    for (int y = 0; y < filteredImage.height(); y++) {
        for (int x = 0; x < filteredImage.width(); x++) {
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
    }
    image = filteredImage;
}

void MorphologicalBasic::erosion(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int, 3>, 3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;

    for (int y = 0; y < filteredImage.height(); y++) {
        for (int x = 0; x < filteredImage.width(); x++) {
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

cimg_library::CImg<unsigned char> MorphologicalBasic::hitOrMiss(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int, 3>, 3> &se) {
    cimg_library::CImg<unsigned char> filteredImage = image;

    for (int y = 0; y < filteredImage.height(); y++) {
        for (int x = 0; x < filteredImage.width(); x++) {
            for (int c = 0; c < image.spectrum(); c++) {
                bool stateHit = true;
                bool stateMiss = true;
                for (int i = 0; i < se.size(); i++) {
                    for (int j = 0; j < se[i].size(); j++) {
                        int new_x = x + i - 1; // se[1][1] is the middle value that is why -1 here and
                        int new_y = y + j - 1; // here -1 too

                        if (new_x >= 0 && new_x < image.width() && new_y >= 0 && new_y < image.height()) {
                            if(se[i][j] == 1 && image(new_x,new_y) != 255) {
                                stateHit = false;
                            }
                            if(se[i][j] == 0 && image(new_x,new_y) != 0) {
                                stateMiss = false;
                            }
                        }
                        else {
                            if (se[i][j] == 1) stateHit = false;
                            if (se[i][j] == 0) stateMiss = false;
                        }
                    }
                }
                if (stateMiss && stateHit) {
                    filteredImage(x,y,0,c) = 255;
                }
                else filteredImage(x,y,0,c) = 0;
            }
        }
    }
    return filteredImage;
}

cimg_library::CImg<unsigned char> morphologicalSubtract(const cimg_library::CImg<unsigned char> &image, const cimg_library::CImg<unsigned char> &hmtResult) {
   cimg_library::CImg<unsigned char> result = image; // Initialize result with original image
    cimg_forXY(image, x, y) {
        result(x, y) = (image(x, y) == 255 && hmtResult(x, y) == 0) ? 255 : 0;
    }
    return result;
}

cimg_library::CImg<unsigned char> thinningHelper(cimg_library::CImg<unsigned char> &image, const std::array<std::array<int, 3>, 3> &se) {
    cimg_library::CImg<unsigned char> hmtResult = MorphologicalBasic::hitOrMiss(image, se); // Perform hit-or-miss
    return morphologicalSubtract(image, hmtResult);       // Subtract result from original image
}

void MorphologicalBasic::thinning(cimg_library::CImg<unsigned char> &image) {
    cimg_library::CImg<unsigned char> previousImage = image; // Initialize with the original image
    cimg_library::CImg<unsigned char> currentImage = image;

    bool hasChanged = true;
    while (hasChanged) {
        hasChanged = false; // Reset change tracker

        for (int i = 1; i <= 8; i++) {
            currentImage = thinningHelper(currentImage, assignNumberToSEThinning(i));
        }

        // Check if the image has changed
        if (!imagesAreEqual(previousImage, currentImage)) {
            hasChanged = true;
            previousImage = currentImage; // Update previous image
        }
    }
    image = currentImage; // Update the input image with the final result

}


void MorphologicalBasic::doOpening(cimg_library::CImg<unsigned char> &image, int se) {
    opening(image,assignNumberToStructuringElement(se));
}
void MorphologicalBasic::doClosing(cimg_library::CImg<unsigned char> &image, int se) {
    closing(image,assignNumberToStructuringElement(se));
}
void MorphologicalBasic::doDilation(cimg_library::CImg<unsigned char> &image, int se) {
    dilation(image,assignNumberToStructuringElement(se));
}
void MorphologicalBasic::doErosion(cimg_library::CImg<unsigned char> &image, int se) {
    erosion(image,assignNumberToStructuringElement(se));
}

cimg_library::CImg<unsigned char> MorphologicalBasic::doHMT(cimg_library::CImg<unsigned char> &image, int se) {
    return hitOrMiss(image,assignNumberToSEHMT(se));
}


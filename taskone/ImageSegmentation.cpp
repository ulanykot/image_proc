//
// Created by MSI on 05.12.2024.
//

#include "ImageSegmentation.h"

#include "MorphologicalBasic.h"

//8 connectivity
void ImageSegmentation::regionGrowing(cimg_library::CImg<unsigned char> &image, int xcoor, int ycoor, int threshold) {
    cimg_library::CImg<unsigned char> result(image.width(), image.height(), 1, 1, 0);
    result(xcoor, ycoor) = 255; // seed

    bool isChanged = true;
    while (isChanged) {
        isChanged = false;

        cimg_forXY(image, x, y) {
            if (result(x, y) == 255) { // checks if pixel is part of the region
                for (int i = -1; i <= 1; i++) {
                    for (int j = -1; j <= 1; j++) {
                        int new_x = x + i;
                        int new_y = y + j;

                        if (MorphologicalBasic::isInRange(image, new_x, new_y)) {
                            if (int difference = std::abs(image(x, y) - image(new_x, new_y)); difference <= threshold && result(new_x, new_y) == 0) {
                                result(new_x, new_y) = 255; // neighbour added when the difference works
                                isChanged = true;
                            }
                        }
                    }
                }
            }
        }
    }

    image = result;
}
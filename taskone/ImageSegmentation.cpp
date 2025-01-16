//
// Created by MSI on 05.12.2024.
//

#include "ImageSegmentation.h"

#include <queue>

#include "HelperFunctions.h"
#include "MorphologicalBasic.h"

//8 connectivity
void ImageSegmentation::regionGrowing(cimg_library::CImg<unsigned char> &image, int xcoor, int ycoor, int threshold,
                                      int hcrit) {
    cimg_library::CImg<unsigned char> result(image.width(), image.height(), 1, 1, 0);
    cimg_library::CImg<bool> mask(image.width(), image.height(), 1, 1, false);
    std::queue<std::pair<int, int> > pixelQueue;

    //initialization of seed with queue
    pixelQueue.push(std::make_pair(xcoor, ycoor));
    mask(xcoor, ycoor) = true;
    result(xcoor, ycoor) = 255; // seed

    // bool isChanged = true;
    while (!pixelQueue.empty()) {
        auto [x, y] = pixelQueue.front(); // Get the front pixel
        pixelQueue.pop();

        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int new_x = x + i;
                int new_y = y + j;

                if (MorphologicalBasic::isInRange(image, new_x, new_y)) {
                    int difference = 0;

                    //calc Euclidean distance between colors
                    if (hcrit == 1) {
                        for (int c = 0; c < image.spectrum(); c++) {
                            difference += std::pow(image(new_x, new_y, 0, c) - image(xcoor, ycoor, 0, c), 2);
                        }
                        difference = std::sqrt(difference);
                    }

                    //calc intensity difference between colors
                    else if (hcrit == 2) {
                        int intensity1 = 0.299 * image(xcoor, ycoor, 0, 0) + 0.587 * image(xcoor, ycoor, 0, 1) + 0.114 *
                                         image(xcoor, ycoor, 0, 2);
                        int intensity2 = 0.299 * image(new_x, new_y, 0, 0) + 0.587 * image(new_x, new_y, 0, 1) + 0.114 *
                                         image(new_x, new_y, 0, 2);
                        difference = std::abs(intensity2 - intensity1);
                    } else if (hcrit == 3) {
                        for (int c = 0; c < image.spectrum(); c++) {
                            difference += std::abs(image(new_x, new_y, 0, c) - image(xcoor, ycoor, 0, c));
                        }
                    }

                    if (difference <= threshold && result(new_x, new_y) == 0) {
                        pixelQueue.push(std::make_pair(new_x, new_y));
                        mask(new_x, new_y) = true;
                        result(new_x, new_y) = 255;
                    }
                }
            }
        }
    }
    image = result;
}

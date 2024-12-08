//
// Created by MSI on 05.12.2024.
//

#include "ImageSegmentation.h"

#include "MorphologicalBasic.h"

//8 connectivity
void ImageSegmentation::regionGrowing(cimg_library::CImg<unsigned char> &image, int xcoor, int ycoor, int threshold) {
    cimg_library::CImg<unsigned char> result(image.width(), image.height(), 1, 1,0);
    result(xcoor, ycoor) = 255; //seed given by user is set to white in an all black image to mark it

    bool isChanged = true;
    while(isChanged) {
        isChanged = false;
        cimg_forXY(image, x, y) {
            for(int c = 0; c < image.spectrum();  c++) {
                if (result(x, y, 1, c) == 255) {
                    for(int i = -1; i <= 1; i++) {
                        for(int j = -1; j <= 1; j++) {
                            int new_x = x + i;
                            int new_y = y + j;

                            if(MorphologicalBasic::isInRange(image,new_x,new_y)) {
                                int difference = std::abs(image(x,y, 0, c)  - image(new_x,new_y, 0, c));
                                if(difference <= threshold && result(new_x, new_y) == 0) {
                                    result(new_x, new_y, 0, c) = 255;
                                    isChanged = true;
                                } //unnecessary setting the rest to 0 because the image already is all zeros at that point
                            }
                        }
                    }
                }
            }
        }
    }
    image = result;
}

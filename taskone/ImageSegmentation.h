//
// Created by MSI on 05.12.2024.
//

#ifndef IMAGESEGMENTATION_H
#define IMAGESEGMENTATION_H
#include "CImg.h"


class ImageSegmentation {
public:
     static void regionGrowing(cimg_library::CImg<unsigned char> &image, int xcoor, int ycoor, int threshold, int hcrit);
};



#endif //IMAGESEGMENTATION_H

//
// Created by MSI on 29.10.2024.
//

#ifndef FILTEROPERATIONS_H
#define FILTEROPERATIONS_H
#include <array>

#include "CImg.h"


class FilterOperations {
public:
    static void minFilter(cimg_library::CImg<unsigned char>& image, int filter_size);
    static void maxFilter(cimg_library::CImg<unsigned char>& image, int filter_size);
    static void medianFilter(cimg_library::CImg<unsigned char>& image, int filter_size);

};



#endif //FILTEROPERATIONS_H

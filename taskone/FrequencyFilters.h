//
// Created by MSI on 19.01.2025.
//

#ifndef FREQUENCYFILTERS_H
#define FREQUENCYFILTERS_H
#include "CImg.h"


class FrequencyFilters {
public:
    static void lowPass(cimg_library::CImg<unsigned char> &image, int area);
    static void highPass(cimg_library::CImg<unsigned char> &image, int area);
    static void bandPass(cimg_library::CImg<unsigned char> &image, int low, int high);
    static void bandCut(cimg_library::CImg<unsigned char> &image, int low, int high);
    static void highPassTwo(cimg_library::CImg<unsigned char> &image, int area);
    static void phaseMod();
};



#endif //FREQUENCYFILTERS_H

//
// Created by MSI on 19.01.2025.
//

#ifndef FREQUENCYFILTERS_H
#define FREQUENCYFILTERS_H
#include "CImg.h"
#include "FourierTransform.h"


class FrequencyFilters {
public:
    static complexVector2D lowPass(complexVector2D imageVector, int area);

    static void doLowPass(cimg_library::CImg<unsigned char> &image, int area);

    static void highPass(cimg_library::CImg<unsigned char> &image, int area);
    static void bandPass(cimg_library::CImg<unsigned char> &image, int center, int bandwidth);
    static void bandCut(cimg_library::CImg<unsigned char> &image, int center, int bandwidth);
    static void highPassTwo(cimg_library::CImg<unsigned char> &image, const cimg_library::CImg<unsigned char> &mask, int area);
    static void phaseMod(cimg_library::CImg<unsigned char> &image, int k, int l);
};



#endif //FREQUENCYFILTERS_H

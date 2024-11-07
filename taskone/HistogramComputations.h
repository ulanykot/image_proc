//
// Created by MSI on 07.11.2024.
//

#ifndef HISTOGRAMCOMPUTATIONS_H
#define HISTOGRAMCOMPUTATIONS_H
#include "CImg.h"


class HistogramComputations {
    public:
    static unsigned char findMax(cimg_library::CImg<unsigned char> &image, int channel);

    static cimg_library::CImg<unsigned char> drawAHistogram(cimg_library::CImg<unsigned char> &image, int channel);

};



#endif //HISTOGRAMCOMPUTATIONS_H

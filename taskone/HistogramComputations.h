//
// Created by MSI on 07.11.2024.
//

#ifndef HISTOGRAMCOMPUTATIONS_H
#define HISTOGRAMCOMPUTATIONS_H
#include <vector>

#include "CImg.h"


class HistogramComputations {
    public:
    static std::vector<int> calcHistogram(cimg_library::CImg<unsigned char> &image, int channel);

    static std::vector<int> calcSumHistogram(std::vector<int> &histogram);

    static cimg_library::CImg<unsigned char> drawHistogram(cimg_library::CImg<unsigned char> &image, int channel);

    static std::vector<int> calcPowerDensityFunction(std::vector<int> &histogramSum, int numberOfPixels, int gmin, int gmax);

    static void applyPowerDensityFunction(cimg_library::CImg<unsigned char> &image,
                                          const std::vector<int> &powerDensityFunction);

    static void equalizedHistogramPower(cimg_library::CImg<unsigned char> &image, int gmin, int gmax);

    cimg_library::CImg<unsigned char> equalizedHistogram(cimg_library::CImg<unsigned char> &image, int channel);
};



#endif //HISTOGRAMCOMPUTATIONS_H

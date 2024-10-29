//
// Created by MSI on 29.10.2024.
//

#ifndef SIMILARITYMEASURES_H
#define SIMILARITYMEASURES_H
#include "CImg.h"


class SimilarityMeasures {
public:
  double meanSquare(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  double peakMeanSquare(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  double signalToNoiseRatio(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  double peakSignalToNoiseRatio(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  double maximumDifference(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
};



#endif //SIMILARITYMEASURES_H

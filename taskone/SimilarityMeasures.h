//
// Created by MSI on 29.10.2024.
//

#ifndef SIMILARITYMEASURES_H
#define SIMILARITYMEASURES_H
#include "CImg.h"


class SimilarityMeasures {
public:
  static double meanSquare(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  static double peakMeanSquare(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  static double signalToNoiseRatio(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  static double peakSignalToNoiseRatio(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image);
  static double maximumDifference(cimg_library::CImg<unsigned char>& first_image, cimg_library::CImg<unsigned char>& second_image) ;
};



#endif //SIMILARITYMEASURES_H

//
// Created by MSI on 12.11.2024.
//

#include "ImageCharacteristics.h"

#include <utility>
#include <vector>

#include "HistogramComputations.h"

double ImageCharacteristics::mean(cimg_library::CImg<unsigned char> image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double sum = 0;
   double mean = 0;
   int numberOfPixels = image.height() * image.width();
   for (int i = 0; i < histogram.size(); i++) {
      sum += histogram[i]*i;
   }
   mean = sum/numberOfPixels;
   return mean;
}

double ImageCharacteristics::variance(cimg_library::CImg<unsigned char> image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double sum = 0;
   double variance = 0;
   int mean = mean(image);
   int numberOfPixels = image.height() * image.width();
   for (int i = 0; i < histogram.size(); i++) {
      sum += pow(i - mean, 2.0) * (histogram[i]);
   }
   variance = sum/numberOfPixels;
   return pow(variance, 2.0);
}

double ImageCharacteristics::standardDeviation(cimg_library::CImg<unsigned char> image) {
   return sqrt(variance(std::move(image)));
}

double ImageCharacteristics::variationCoefficient(cimg_library::CImg<unsigned char> image) {
   double mean = mean(image);
   double standardDeviation = standardDeviation(std::move(image));
   return standardDeviation/mean;
}

double ImageCharacteristics::asymmetryCoefficient(cimg_library::CImg<unsigned char> image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double mean = mean(image);
   double standardDeviation = standardDeviation(std::move(image));
   int numberOfPixels = image.height() * image.width();
   double asymmetryCoefficient = 0;
   double sum = 0;
   for (int i = 0; i < histogram.size(); i++) {
      sum += pow(i - mean, 3.0) * (histogram[i]);
   }
   asymmetryCoefficient = sum/numberOfPixels*pow(standardDeviation, 1.0/3.0);
   return asymmetryCoefficient;
}

double ImageCharacteristics::flatteningCoefficient(cimg_library::CImg<unsigned char> image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double mean = mean(image);
   double standardDeviation = standardDeviation(std::move(image));
   int numberOfPixels = image.height() * image.width();
   double flatteningCoefficient = 0;
   double sum = 0;
   for (int i = 0; i < histogram.size(); i++) {
      sum += pow(i - mean, 4.0)*(histogram[i]) - 3;
   }
   flatteningCoefficient = sum/numberOfPixels*pow(standardDeviation, 1.0/4.0);
   return flatteningCoefficient;
}

double ImageCharacteristics::variationCoefficient2(cimg_library::CImg<unsigned char> image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double sumAbsolute = 0;
   double numberOfPixels = image.height() * image.width();
   double variationCoefficient2 = 0;
   for (int i = 0; i < histogram.size(); i++) {
      sumAbsolute += pow(abs(histogram[i]), 2.0);
   }
   variationCoefficient2 = sumAbsolute/pow(1/numberOfPixels,2.0);
   return variationCoefficient2;
}

double ImageCharacteristics::informationSourceEntropy(cimg_library::CImg<unsigned char> image) {
   double numberOfPixels = image.height() * image.width();
   double sum = 0;
   double informationSourceEntropy = 0;
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   for (int i = 0; i < histogram.size(); i++) {
      sum += histogram[i]*log2(histogram[i]/numberOfPixels);
   }
   informationSourceEntropy = -1 * (sum/numberOfPixels);
   return informationSourceEntropy;
}


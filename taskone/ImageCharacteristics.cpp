//
// Created by MSI on 12.11.2024.
//

#include "ImageCharacteristics.h"

#include <utility>
#include <vector>

#include "HistogramComputations.h"

double ImageCharacteristics::meanFunction(cimg_library::CImg<unsigned char> &image) {
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

double ImageCharacteristics::variance(cimg_library::CImg<unsigned char> &image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double sum = 0;
   double variance = 0;
   int mean = meanFunction(image);
   int numberOfPixels = image.height() * image.width();
   for (int i = 0; i < histogram.size(); i++) {
      sum += pow(i - mean, 2.0) * (histogram[i]);
   }
   variance = sum/numberOfPixels;
   return pow(variance, 2.0);
}

double ImageCharacteristics::standardDeviation(cimg_library::CImg<unsigned char> &image) {
   return sqrt(variance(image));
}

double ImageCharacteristics::variationCoefficient(cimg_library::CImg<unsigned char> &image) {
   double mean = meanFunction(image);
   double standardDev = standardDeviation(image);
   return standardDev/mean;
}

double ImageCharacteristics::asymmetryCoefficient(cimg_library::CImg<unsigned char> &image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double mean = meanFunction(image);
   double standardDev = standardDeviation(image);
   int numberOfPixels = image.height() * image.width();
   double asymmetryCoefficient = 0;
   double sum = 0;
   for (int i = 0; i < histogram.size(); i++) {
      sum += pow(i - mean, 3.0) * (histogram[i]);
   }
   asymmetryCoefficient = sum/numberOfPixels*pow(standardDev, 1.0/3.0);
   return asymmetryCoefficient;
}

double ImageCharacteristics::flatteningCoefficient(cimg_library::CImg<unsigned char> &image) {
   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   double mean = meanFunction(image);
   double standardDev = standardDeviation(image);
   int numberOfPixels = image.height() * image.width();
   double flatteningCoefficient = 0;
   double sum = 0;
   for (int i = 0; i < histogram.size(); i++) {
      sum += pow(i - mean, 4.0)*(histogram[i]) - 3;
   }
   flatteningCoefficient = sum/numberOfPixels*pow(standardDev, 1.0/4.0);
   return flatteningCoefficient;
}

double ImageCharacteristics::variationCoefficient2(cimg_library::CImg<unsigned char> &image) {
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

double ImageCharacteristics::informationSourceEntropy(cimg_library::CImg<unsigned char> &image) {
   double numberOfPixels = image.height() * image.width();
   double sum = 0;

   std::vector<int> histogram = HistogramComputations::calcHistogram(image,0);
   for (int i = 0; i < histogram.size(); i++) {
      double count = histogram[i];
      if (count > 0) {  
         double probability = count / numberOfPixels;
         sum += probability * log2(probability);  
      }
   }

   double informationSourceEntropy = -sum;  
   return informationSourceEntropy;
}


//
// Created by MSI on 17.11.2024.
//

#ifndef SPATIALOPERATIONS_H
#define SPATIALOPERATIONS_H
#include "CImg.h"


class SpatialOperations {
public:
    static int h1[3][3];
    static int h2[3][3];
    static int h3[3][3];
    //linear spatial
    static void convolve(cimg_library::CImg<unsigned char> &image, int mask[3][3]);
    //nonlinear spatial
    static void rosenfeldOperator(cimg_library::CImg<unsigned char> &image, int power);
    static void edgeSharpening(cimg_library::CImg<unsigned char> &image, int mask);
    //TODO
    static void optimizedEdgeSharpening(cimg_library::CImg<unsigned char> &image, int mask);

};



#endif //SPATIALOPERATIONS_H

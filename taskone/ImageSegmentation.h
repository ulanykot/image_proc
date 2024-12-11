#ifndef IMAGESEGMENTATION_H
#define IMAGESEGMENTATION_H

#include <array>
#include <queue>
#include <vector>
#include <cmath>

#include "CImg.h"

using namespace cimg_library;
using namespace std;


class ImageSegmentation {
public:
    static void regionGrowing(CImg<unsigned char> &image, int seedX, int seedY, int threshold, int distance);
    static double calculateDistance(int r1, int g1, int b1, int r2, int g2, int b2, int distance);
};

#endif //IMAGESEGMENTATION_H
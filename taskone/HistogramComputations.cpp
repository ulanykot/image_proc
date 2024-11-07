//
// Created by MSI on 07.11.2024.
//

#include "HistogramComputations.h"

#include <vector>
unsigned char HistogramComputations::findMax(cimg_library::CImg<unsigned char>& image, int channel) {
    unsigned char max = 0;
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            max = std::max(max, image(x,y,0,channel));
        }
    }
    return max;
}
cimg_library::CImg<unsigned char> HistogramComputations::drawAHistogram(cimg_library::CImg<unsigned char>& image, int channel) {
    std::vector<int> histogram(256, 0);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            int intensity = image(x,y,0,channel);
            histogram[intensity]++;
        }
    }
    int max_count = *std::max_element(histogram.begin(), histogram.end());

    cimg_library::CImg<unsigned char> histogram_image(256, 256);
    cimg_forXY(histogram_image,x,y) {
        histogram_image(x,y) = 0;
    }
    for (int x = 0; x < histogram_image.width(); x++) {
        float barHeight = (histogram[x] / static_cast<float>(max_count)) * histogram_image.height();
        for (int y = histogram_image.height() - 1; y >= histogram_image.height() - barHeight; y--) {
            histogram_image(x,y) = 255;
        }
    }
    return histogram_image;
}


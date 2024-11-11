//
// Created by MSI on 07.11.2024.
//

#include "HistogramComputations.h"

std::vector<int> HistogramComputations::calcHistogram(cimg_library::CImg<unsigned char> &image, int channel) {
    std::vector<int> histogram(256, 0);
    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            int intensity = image(x,y,0,channel);
            histogram[intensity]++;
        }
    }
    return histogram;
}

std::vector<int> HistogramComputations::calcSumHistogram(std::vector<int> &histogram) {
    std::vector<int> sum(256, 0);
    sum[0] = histogram[0];
    for (int x = 1; x < histogram.size(); x++) {
        sum[x] += sum[x -1] + histogram[x];
    }
    return sum;
}

cimg_library::CImg<unsigned char> HistogramComputations::drawHistogram(cimg_library::CImg<unsigned char>& image, int channel) {
    std::vector<int> histogram = calcHistogram(image, channel);
    int max_count = *std::max_element(histogram.begin(), histogram.end());

    cimg_library::CImg<unsigned char> histogram_image(256, 256);
    cimg_forXY(histogram_image,x,y) {
        histogram_image(x,y) = 0;
    }
    for (int x = 0; x < histogram_image.width(); x++) {
        float barHeight = (histogram[x] / static_cast<float>(max_count)) * histogram_image.height();
        for (int y = histogram_image.height() - 1; y >= histogram_image.height() - barHeight; y--) {
            histogram_image(x,y,0,0) = 255;
        }
    }
    return histogram_image;
}

std::vector<int> HistogramComputations::calcPowerDensityFunction(std::vector<int>& histogramSum, int numberOfPixels,
    int gmin, int gmax) {
    std::vector<int> powerDensityFunction(256, 0);
    float thirdPowerOfGmin = pow(gmin, 1.0f / 3.0f);
    float thirdPowerOfGmax = pow(gmax, 1.0f / 3.0f);

    for (int f = 0; f < 256; f++) {
        int cumulativeSum = histogramSum[f];
        float resultCubed = thirdPowerOfGmin + (thirdPowerOfGmax - thirdPowerOfGmin) * (static_cast<float>(cumulativeSum)/numberOfPixels);
        int newBrightness = static_cast<int>(std::round(std::pow(resultCubed, 3.0f)));
        powerDensityFunction[f] = std::max(gmin, std::min(newBrightness, gmax));
    }
    return powerDensityFunction;
}

void HistogramComputations::applyPowerDensityFunction(cimg_library::CImg<unsigned char>& image, const std::vector<int>& powerDensityFunction, int channel) {
    cimg_forXY(image, x, y) {
        int originalBrightness = image(x, y, 0, channel);
        image(x, y, 0, channel) = powerDensityFunction[originalBrightness];
    }
}

void HistogramComputations::equalizedHistogramPower(
    cimg_library::CImg<unsigned char> &image, int channel, int gmin, int gmax) {
    std::vector<int> histogram = HistogramComputations::calcHistogram(image, channel);
    std::vector<int> cumulativeHistogram = HistogramComputations::calcSumHistogram(histogram);
    int numberOfPixels = image.width() * image.height();
    std::vector<int> powerDensityFunction = calcPowerDensityFunction(cumulativeHistogram,numberOfPixels, gmin, gmax);
    applyPowerDensityFunction(image,powerDensityFunction,channel);
}


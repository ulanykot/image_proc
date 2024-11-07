//
// Created by MSI on 29.10.2024.
//

#include "SimilarityMeasures.h"

double SimilarityMeasures::meanSquare(cimg_library::CImg<unsigned char> &first_image, cimg_library::CImg<unsigned char> &second_image) {
    int M = first_image.width();
    int N = first_image.height();
    int channels = first_image.spectrum();
    double mean_square = 0;

    for (int c = 0; c < channels; ++c)
        for(int x = 0; x < M; ++x) {
            for(int y = 0; y< N; ++y) {
                double difference = first_image(x, y,0,c) - second_image(x, y,0,c);
                mean_square += difference*difference;
            }
        }
    mean_square /= M*N*channels;
    return mean_square;
}

double SimilarityMeasures::peakMeanSquare(cimg_library::CImg<unsigned char> &first_image, cimg_library::CImg<unsigned char> &second_image) {
    double peak_mean_square = 0;
    double max_pixel_value = first_image.max();
    double mean_square = meanSquare(first_image, second_image);
    peak_mean_square = mean_square / (max_pixel_value*max_pixel_value);
    return peak_mean_square;

}

double SimilarityMeasures::signalToNoiseRatio(cimg_library::CImg<unsigned char> &first_image, cimg_library::CImg<unsigned char> &second_image) {
    int M = first_image.width();
    int N = first_image.height();
    int channels = first_image.spectrum();
    double signal_to_noise_ratio = 0;
    double difference_val = 0;
    double first_image_val = 0;

    for (int c = 0; c < channels; ++c) {
        for(int x = 0; x < M; ++x) {
            for(int y = 0; y < N; ++y) {
                first_image_val += first_image(x, y,0,c) * first_image(x, y,0,c);
            }
        }
    }

    for (int c = 0; c < channels; ++c) {
        for(int x = 0; x < M; ++x) {
            for(int y = 0; y< N; ++y) {
                double difference = first_image(x, y,0,c) - second_image(x, y,0,c);
                difference_val += difference*difference;
            }
        }
    }
    signal_to_noise_ratio = 10 * log10(first_image_val / difference_val);
    return signal_to_noise_ratio;
}

double SimilarityMeasures::peakSignalToNoiseRatio(cimg_library::CImg<unsigned char> &first_image, cimg_library::CImg<unsigned char> &second_image) {
    int M = first_image.width();
    int N = first_image.height();
    int channels = first_image.spectrum();
    double peak_signal_to_noise_ratio = 0;
    double difference_val = 0;
    double first_image_max = first_image.max();
    double first_image_val_max = 0;

    for (int c = 0; c < channels; ++c) {
        for(int x = 0; x < M; ++x) {
            for(int y = 0; y < N; ++y) {
                first_image_val_max += first_image_max * first_image_max;
            }
        }
    }

    for (int c = 0; c < channels; ++c) {
        for(int x = 0; x < M; ++x) {
            for(int y = 0; y< N; ++y) {
                double difference = first_image(x, y,0,c) - second_image(x, y,0,c);
                difference_val += difference*difference;
            }
        }
    }
    peak_signal_to_noise_ratio = 10 * log10(first_image_val_max / difference_val);
    return peak_signal_to_noise_ratio;
}

double SimilarityMeasures::maximumDifference(cimg_library::CImg<unsigned char> &first_image, cimg_library::CImg<unsigned char> &second_image) {
    int M = first_image.width();
    int N = first_image.height();
    int channels = first_image.spectrum();
    double max_difference = 0.0;

    for (int c = 0; c < channels; ++c) {
        for(int x = 0; x < M; ++x) {
            for(int y = 0; y < N; ++y) {
                double difference = std::abs(second_image(x, y,0,c) - first_image(x, y,0,c));
                if(difference > max_difference) {
                    max_difference = difference;
                }
            }
        }
    }
    return max_difference;
}



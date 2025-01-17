//
// Created by MSI on 16.01.2025.
//

#ifndef FOURIERTRANSFORM_H
#define FOURIERTRANSFORM_H
#include <complex>
#include <vector>

#include "CImg.h"

using complex = std::complex<double>;
using complexVector = std::vector<complex>;
using complexVector2D = std::vector<complexVector>;

class FourierTransform {
public:
    static complexVector2D imageToComplexVector(cimg_library::CImg<unsigned char>& image);
    static cimg_library::CImg<unsigned char> vectorToImage(complexVector2D& fourier);
    // 1D vector
    static void DFT1D(complexVector& vector, bool inverse);
    static void FFT1D(complexVector& vector, bool inverse);

    // full
    static complexVector2D discreteFourier(cimg_library::CImg<unsigned char>& image, bool inverse);
    static complexVector2D fastFourier(cimg_library::CImg<unsigned char>& image, bool inverse);

    //visualization
    static cimg_library::CImg<unsigned char> visualizeSpectrum(complexVector2D& vector);
};



#endif //FOURIERTRANSFORM_H

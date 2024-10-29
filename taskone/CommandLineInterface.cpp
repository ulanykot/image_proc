//
// Created by MSI on 29.10.2024.
//

#include "CommandLineInterface.h"

#include <iostream>
#include <string>

#include "BasicOperations.h"
#include "CImg.h"
#include "FilterOperations.h"
#include "SimilarityMeasures.h"

void CommandLineInterface::parseCommand(int argc, char *argv[]) {
    if (argc < 3) {
        help();
        return;
    }

    std::string inputImage = argv[1];  // the input image file
    std::string command = argv[2];    // the command (e.g., --brightness or --contrast

    // Load the image
    cimg_library::CImg<unsigned char> image(inputImage.c_str());


    // Apply the appropriate command
    if (command == "--brightness") {
        if (argc < 4) {
            std::cout << "Error: Missing parameter for brightness adjustment." << std::endl;
            return;
        }
        std::string param = argv[3]; // the parameter for the command (e.g., value to adjust
        int brightnessValue = atoi(param.c_str()); // Convert param to integer
        BasicOperations::doBrightness(image, brightnessValue);
    }
    else if (command == "--contrast") {
        if (argc < 4) {
            std::cout << "Error: Missing parameter for contrast adjustment." << std::endl;
            return;
        }
        std::string param = argv[3]; // the parameter for the command (e.g., value to adjust
        float contrastFactor = atof(param.c_str()); // Convert param to float
        BasicOperations::doContrast(image, contrastFactor);
    }
    else if(command == "--negative") {
        BasicOperations::doNegative(image);
    }
    else if(command =="--hflip") {
        BasicOperations::doHorizontalFlip(image);
    }
    else if(command =="--vflip") {
        BasicOperations::doVerticalFlip(image);
    }
    else if(command == "--help") {
        CommandLineInterface::help();
    }
    else if(command =="--dflip") {
        BasicOperations::doDiagonalFlip(image);
    }
    else if(command =="--shrink") {
        if (argc < 4) {
            std::cout << "Error: Missing parameter for shrinking image." << std::endl;
            return;
        }
        std::string param = argv[3];
        float shrinkFactor = atof(param.c_str()); // Convert param to float
        BasicOperations::doImageShrinking(image, shrinkFactor);
    }
    else if(command =="--enlarge") {
        if (argc < 4) {
            std::cout << "Error: Missing parameter for enlarging image." << std::endl;
            return;
        }
        std::string param = argv[3];
        float enlargeFactor = atof(param.c_str()); // Convert param to float
        BasicOperations::doImageEnlargement(image, enlargeFactor);
    }
    else if(command =="--min") {
        int filter_size = (argc >= 4) ? atoi(argv[3]) : 3; // default filter size is 3
        FilterOperations::minFilter(image, filter_size);
    }
    else if(command =="--max") {
        int filter_size = (argc >= 4) ? atoi(argv[3]) : 3; // default filter size is 3
        FilterOperations::maxFilter(image, filter_size);
    }
    else if(command =="--median") {
        int filter_size = (argc >= 4) ? atoi(argv[3]) : 3; // default filter size is 3
        FilterOperations::medianFilter(image, filter_size);
    }
    else if(command =="--mse") {
        std::string outputImage = argv[3]; // the output image file
        cimg_library::CImg<unsigned char> outImage(outputImage.c_str());
        std::cout<<SimilarityMeasures::meanSquare(image,outImage);
        return;
    }
    else if(command =="--pmse") {
        std::string outputImage = argv[3]; // the output image file
        cimg_library::CImg<unsigned char> outImage(outputImage.c_str());
        std::cout<<SimilarityMeasures::peakMeanSquare(image,outImage);
        return;
    }
    else if(command =="--snr") {
        std::string outputImage = argv[3]; // the output image file
        cimg_library::CImg<unsigned char> outImage(outputImage.c_str());
        std::cout<<SimilarityMeasures::signalToNoiseRatio(image,outImage);
        return;
    }
    else if(command =="--psnr") {
        std::string outputImage = argv[3]; // the output image file
        cimg_library::CImg<unsigned char> outImage(outputImage.c_str());
        std::cout<<SimilarityMeasures::peakSignalToNoiseRatio(image,outImage);
        return;
    }
    else if(command =="--md") {
        std::string outputImage = argv[3]; // the output image file
        cimg_library::CImg<unsigned char> outImage(outputImage.c_str());
        std::cout<<SimilarityMeasures::maximumDifference(image,outImage);
        return;
    }
    else {
        std::cout << "Unknown command: " << command << std::endl;
        return;
    }

    // Save the modified image
    image.save_bmp("outcm.bmp");
    std::cout << "Modified image saved as 'outcm.bmp'" << std::endl;

}

void CommandLineInterface::help() {
        std::cout << "Usage: application <path to image_file> <command> [param]" << std::endl;
        std::cout << "Possible commands: " << std::endl;
        std::cout << "--brightness <value>  : Adjusts the image's brightness by adding a specified integer value (0-255) to each pixel." << std::endl;
        std::cout << "--contrast <value>    : Adjusts the image's contrast. A value greater than 1 increases contrast, while a value between 0 and 1 decreases it." << std::endl;
        std::cout << "--negative            : Inverts the colors of the image, creating a negative effect." << std::endl;
        std::cout << "--hflip               : Flips the image horizontally, mirroring it across the vertical axis." << std::endl;
        std::cout << "--vflip               : Flips the image vertically, mirroring it across the horizontal axis." << std::endl;
        std::cout << "--dflip               : Flips the image both horizontally and vertically, resulting in a diagonal flip." << std::endl;
        std::cout << "--shrink <factor>     : Shrinks the image by a specified factor (0-1), reducing its dimensions. E.g., 0.5 reduces the size by 50%." << std::endl;
        std::cout << "--enlarge <factor>    : Enlarges the image by a specified factor (>1), increasing its dimensions. E.g., 2 doubles the image size." << std::endl;
        std::cout << "--min <filter_size>   : Applies a minimum filter of specified size (odd integer, e.g., 3, 5) to reduce noise by keeping the minimum pixel value in a neighborhood." << std::endl;
        std::cout << "--max <filter_size>   : Applies a maximum filter of specified size (odd integer, e.g., 3, 5) to enhance bright spots by keeping the maximum pixel value in a neighborhood." << std::endl;
        std::cout << "--median <filter_size>: Applies a median filter of specified size (odd integer, e.g., 3, 5) to reduce noise by setting each pixel to the median of its neighborhood." << std::endl;
    }


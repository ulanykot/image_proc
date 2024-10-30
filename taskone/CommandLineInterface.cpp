//
// Created by MSI on 29.10.2024.
//

#include "CommandLineInterface.h"

#include <iostream>
#include <string>
#include <vector>

#include "BasicOperations.h"
#include "CImg.h"
#include "FilterOperations.h"
#include "SimilarityMeasures.h"

void CommandLineInterface::parseCommand(int argc, char *argv[]) {
    if (argc < 3) {
        help();
        return;
    }

    std::string inputImage = argv[1];
    std::string outputImage = argv[2];
    std::vector<std::string> commands;

    for (int i = 3; i < argc; ++i) {
        commands.push_back(argv[i]);
    }

    cimg_library::CImg<unsigned char> image(inputImage.c_str());
    cimg_library::CImg<unsigned char> outImage;
    bool comparisonImageLoaded = false;

    int index = 3; // Starting from argv[3]
    while (index < argc) {
        std::string command = argv[index];
        if (command == "--brightness" || command == "--contrast" || command == "--shrink" || command == "--enlarge" || command == "--min" || command == "--max" || command == "--median") {
            if (index + 1 >= argc) {
                std::cout << "Error: Missing parameter for " << command << " adjustment." << std::endl;
                return;
            }
            int parameter = std::atoi(argv[++index]);  // Get the parameter following the command
            if (command == "--brightness") {
                BasicOperations::doBrightness(image, parameter);
            } else if (command == "--contrast") {
                BasicOperations::doContrast(image, static_cast<float>(parameter));
            } else if (command == "--shrink") {
                BasicOperations::doImageShrinking(image, static_cast<float>(parameter));
            } else if (command == "--enlarge") {
                BasicOperations::doImageEnlargement(image, static_cast<float>(parameter));
            } else if (command == "--min") {
                FilterOperations::minFilter(image, parameter);
            } else if (command == "--max") {
                FilterOperations::maxFilter(image, parameter);
            } else if (command == "--median") {
                FilterOperations::medianFilter(image, parameter);
            }
        } else if (command == "--negative") {
            BasicOperations::doNegative(image);
        } else if (command == "--hflip") {
            BasicOperations::doHorizontalFlip(image);
        } else if (command == "--vflip") {
            BasicOperations::doVerticalFlip(image);
        } else if (command == "--dflip") {
            BasicOperations::doDiagonalFlip(image);
        } else if (command == "--mse" || command == "--pmse" || command == "--snr" || command == "--psnr" || command == "--md") {
            if (!comparisonImageLoaded) {
                outImage.load(outputImage.c_str());
                comparisonImageLoaded = true;
            }
            if (command == "--mse") {
                std::cout << "Mean square error: " << SimilarityMeasures::meanSquare(image, outImage) << std::endl;
            } else if (command == "--pmse") {
                std::cout << "Peak mean square error: " << SimilarityMeasures::peakMeanSquare(image, outImage) << std::endl;
            } else if (command == "--snr") {
                std::cout << "Signal to noise ratio: " << SimilarityMeasures::signalToNoiseRatio(image, outImage) << std::endl;
            } else if (command == "--psnr") {
                std::cout << "Peak signal to noise ratio: " << SimilarityMeasures::peakSignalToNoiseRatio(image, outImage) << std::endl;
            } else if (command == "--md") {
                std::cout << "Max difference: " << SimilarityMeasures::maximumDifference(image, outImage) << std::endl;
            }
        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
        ++index;  // Move to the next argument
    }

    if (!comparisonImageLoaded) {
        image.save(outputImage.c_str());
        std::cout << "Modified image saved as '" << outputImage << "'" << std::endl;
    }
}

void CommandLineInterface::help() {
    std::cout << "Usage: application <input_image_file> <output_image_file> <command(s)> [param]" << std::endl;
    std::cout << "Possible commands: " << std::endl;
    std::cout << "--brightness <value>      - Adjusts the image's brightness." << std::endl;
    std::cout << "--contrast <value>        - Adjusts the image's contrast." << std::endl;
    std::cout << "--negative                - Inverts the colors of the image." << std::endl;
    std::cout << "--hflip                   - Flips the image horizontally." << std::endl;
    std::cout << "--vflip                   - Flips the image vertically." << std::endl;
    std::cout << "--dflip                   - Diagonal flip of the image." << std::endl;
    std::cout << "--shrink <factor>         - Shrinks the image." << std::endl;
    std::cout << "--enlarge <factor>        - Enlarges the image." << std::endl;
    std::cout << "--min <filter_size>       - Applies a minimum filter." << std::endl;
    std::cout << "--max <filter_size>       - Applies a maximum filter." << std::endl;
    std::cout << "--median <filter_size>    - Applies a median filter." << std::endl;
    std::cout << "--mse, --pmse, --snr, --psnr, --md - Multiple similarity commands can be used together to compare images." << std::endl;
}

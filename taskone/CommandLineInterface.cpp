//
// Created by MSI on 29.10.2024.
//

#include "CommandLineInterface.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <fstream>

#include "BasicOperations.h"
#include "CImg.h"
#include "FilterOperations.h"
#include "HistogramComputations.h"
#include "ImageCharacteristics.h"
#include "ImageSegmentation.h"
#include "MorphologicalBasic.h"
#include "SimilarityMeasures.h"
#include "SpatialOperations.h"

bool isValidImageFile(const std::string& filePath) {
    std::ifstream file(filePath);
    return file.good();
}

void printSingleMatrix(const std::array<std::array<int, 3>, 3> &h1) {
    for (int i = 0; i < 3; ++i) {
        // Loop through rows
        for (int j = 0; j < 3; ++j) {
            std::cout << h1[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}


void CommandLineInterface::parseCommand(int argc, char *argv[]) {
    if (!isValidImageFile(argv[1])) {
        std::cerr << "Error: File \"" << argv[1] << "\" does not exist." << std::endl;
        return;
    }

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
    bool isKnownCommand = true;


    int index = 3; // Starting from argv[3]
    while (index < argc) {
        std::string command = argv[index];
        if (command == "--brightness" || command == "--contrast" || command == "--shrink" || command == "--enlarge" || command == "--min"
            || command == "--max" || command == "--median"|| command == "--histogram" || command == "--hpower" || command == "--orosenfeld" || command == "--sedgesharp" ||
            command =="--erosion" || command =="--closing" || command =="--opening" || command == "--dilation" || command == "--hmt" || command == "--rgrowing") {
            if (index + 1 >= argc) {
                std::cout << "Error: Missing parameter for " << command << " adjustment." << std::endl;
                return;
            }
            std::string parameter = argv[++index];  // Get the parameter following the command
            if (command == "--brightness") {
                BasicOperations::doBrightness(image, atoi(parameter.c_str()));
            } else if (command == "--contrast") {
                BasicOperations::doContrast(image, atof(parameter.c_str()));
            } else if (command == "--shrink") {
                BasicOperations::doImageShrinking(image, atof(parameter.c_str()));
            } else if (command == "--enlarge") {
                BasicOperations::doImageEnlargement(image, atof(parameter.c_str()));
            } else if (command == "--min") {
                FilterOperations::minFilter(image, atoi(parameter.c_str()));
            } else if (command == "--max") {
                FilterOperations::maxFilter(image, atoi(parameter.c_str()));
            } else if (command == "--median") {
                FilterOperations::medianFilter(image, atoi(parameter.c_str()));
            }
            else if(command == "--sedgesharp") {
                SpatialOperations::edgeSharpening(image, atoi(parameter.c_str()));
            }
            else if (command == "--orosenfeld") {
                SpatialOperations::rosenfeldOperator(image, atoi(parameter.c_str()));
            }
            else if (command == "--hpower") {
                if (index + 1 >= argc) {
                    std::cout << "Error: --hpower requires parameters gmin and gmax)." << std::endl;
                    return;
                }
                int gmin = atoi(parameter.c_str());
                int gmax = atoi(argv[++index]);

                // Apply histogram equalization with power density function
                HistogramComputations::equalizedHistogramPower(image, gmin, gmax);
                cimg_library::CImg<unsigned char> newImage = HistogramComputations::drawHistogram(image,0);
                int pos = outputImage.find_last_of(".bmp");
                std::string histogramPath;
                if (pos != std::string::npos) {
                    histogramPath = outputImage.substr(0, pos - 3) + "histogram.bmp";
                } else {
                    histogramPath = outputImage + "histogram.bmp";
                }
                newImage.save(histogramPath.c_str());
                std::cout << "Histogram of changed image with power density function saved as: '" + histogramPath + "'" << std::endl;
                //return;
            }
            else if(command == "--histogram") {
                cimg_library::CImg<unsigned char> newImage = HistogramComputations::drawHistogram(image,atoi(parameter.c_str()));
                newImage.save(outputImage.c_str());
                std::cout<<"Histogram representation in the form of an image saved." <<std::endl;
                return;
            }
            else if(command == "--dilation") {
                MorphologicalBasic::doDilation(image,atoi(parameter.c_str()));
            }
            else if(command == "--erosion") {
                MorphologicalBasic::doErosion(image,atoi(parameter.c_str()));
            }
            else if(command == "--opening") {
                MorphologicalBasic::doOpening(image,atoi(parameter.c_str()));
            }
            else if(command == "--closing") {
                MorphologicalBasic::doClosing(image,atoi(parameter.c_str()));
            }
            else if(command =="--hmt") {
                cimg_library::CImg<unsigned char> newImage = MorphologicalBasic::doHMT(image,atoi(parameter.c_str()));
                newImage.save(outputImage.c_str());
                return;
            }
            else if (command =="--rgrowing") {
                ImageSegmentation::regionGrowing(image,128,128,220);
            }

        } else if (command == "--negative") {
            BasicOperations::doNegative(image);
        } else if (command == "--hflip") {
            BasicOperations::doHorizontalFlip(image);
        } else if (command == "--vflip") {
            BasicOperations::doVerticalFlip(image);
        } else if (command == "--dflip") {
            BasicOperations::doDiagonalFlip(image);
        }
        else if(command == "--thinning") {
            MorphologicalBasic::thinning(image);
        }
        else if (command == "--time") {
            // Measure time for non-optimized version
            int a[3][3] = { {0, -1, 0}, {-1, 5, -1}, {0, -1, 0} };
            auto start = std::chrono::high_resolution_clock::now();
            SpatialOperations::convolve(image, a); // Call the function
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = duration_cast<std::chrono::milliseconds>(end - start).count();
            std::cout << "Convolve function time: " << duration << " ms" << std::endl;

            // Measure time for optimized version
            auto startOpt = std::chrono::high_resolution_clock::now();
            SpatialOperations::optimizedEdgeSharpening(image); // Call the function
            auto endOpt = std::chrono::high_resolution_clock::now();
            auto durationOpt = duration_cast<std::chrono::milliseconds>(endOpt - startOpt).count();
            std::cout << "Optimized function time: " << durationOpt << " ms" << std::endl;
        }
        else if (command=="--help") {
            help();
            return;
        } else if (command == "--mse" || command == "--pmse" || command == "--snr" || command == "--psnr" || command == "--md"
            //task2
            || command == "--cmean" || command == "--cvariance" || command == "--cstdev" || command == "--cvarcoi"
            || command =="--casyco" || command == "--cfsyco" || command == "--cvarcoii" || command == "--centropy") {
            if (isValidImageFile(argv[2])) {
                if (!comparisonImageLoaded) {
                    outImage.load(outputImage.c_str());
                    comparisonImageLoaded = true;
                }
            }
            else {
                std::cerr << "Error: File \"" << argv[2] << "\" does not exist." << std::endl;
                return;
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
            else if (command == "--cmean") {
                std::cout<< "Mean: " << ImageCharacteristics::meanFunction(image) << std::endl;
            }
            else if (command == "--cvariance") {
                std::cout<< "Variance: " << ImageCharacteristics::variance(image) << std::endl;
            }
            else if (command == "--cstdev") {
                std::cout<< "Standard deviation: " << ImageCharacteristics::standardDeviation(image) << std::endl;
            }
            else if(command == "--cvarcoi") {
                std::cout<<"Variation coefficient I: " << ImageCharacteristics::variationCoefficient(image) << std::endl;
            }
            else if (command == "--cfsyco") {
                std::cout<<"Flattening coeffcient: " << ImageCharacteristics::flatteningCoefficient(image) << std::endl;
            }
            else if (command == "--casyco") {
                std::cout<<"Asymmetry coeffcient: " << ImageCharacteristics::asymmetryCoefficient(image) << std::endl;
            }
            else if (command == "--cvarcoii") {
                std::cout<<"Variation coeffcient II: " << ImageCharacteristics::variationCoefficient2(image) << std::endl;
            }
            else if (command == "--centropy") {
                std::cout<<"Information source entropy: " << ImageCharacteristics::informationSourceEntropy(image) << std::endl;
            }

        } else {
            std::cout << "Unknown command: " << command << std::endl;
        }
        ++index;
    }

    if (!comparisonImageLoaded) {
        image.save(outputImage.c_str());
        std::cout << "Modified image saved as '" << outputImage << "'" << std::endl;
    }
}

void CommandLineInterface::help() {
    int param;
    std::cout << "Usage: application <input_image_file> <output_image_file> <command(s)> [param]" << std::endl;
    std::cout << "Pick which task you want the commands of:" << std::endl;
    std::cout << "0 - ALL, 1 - FIRST, 2 - SECOND, etc. 5 - ALL SE." << std::endl;
    std::cin >> param;
    switch(param) {
        case 1:
            std::cout << "\t TASK ONE COMMANDS" << std::endl;
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
        break;
        case 2:
            std::cout <<"\t TASK TWO COMMANDS" << std::endl;
            std::cout<<"--sedgesharp <value>        - Applies a edge sharpening mask linear image filtration algorithm. The available values are 1, 2, 3. The matrices look as follows:" << std::endl;
            printMatrix(SpatialOperations::h1, SpatialOperations::h2, SpatialOperations::h3);
            std::cout<<"--hpower                    - Applies a power density function to the histogram. Gives two outputs: an changed image and an image histogram." <<std::endl;
            std::cout<<"--orosenfeld                - Applies a rosenfeld operator non-linear spatial filtration algorithm."<<std::endl;
            std::cout<< "--cmean --cvariance --cstdev --cvarcoi --casyco --cfsyco --cvarcoii --centropy     - Multiple image characteristic parameters that can be used together to display values." << std::endl;
        break;
        case 3:
            std::cout <<"\t TASK THREE COMMANDS" << std::endl;
        std::cout<<"--dilation <structuring_element_number>                    - Applies dilation operation with a given structuring element." << std::endl;
        std::cout <<"--erosion <structuring_element_number>                    - Applies erosion operation with a given structuring element." << std::endl;
        std::cout <<"--opening <structuring_element_number>                    - Applies opening operation with a given structuring element. It is dilated erosion." << std::endl;
        std::cout <<"--closing <structuring_element_number>                    - Applies closing operation with a given structuring element. It is eroded dilation." << std::endl;
        std::cout <<"--hmt <structuring_element_number>                        - Applies hit-or-miss operation with a given structuring element." << std::endl;
        std::cout <<"--thinning                                                - Applies thinning operation. No parameter needed." << std::endl;
        std::cout <<"--rgrowing <x> <y> <threshold>                            - Applies region growing with a <threshold> a seed pixel at (<x>,<y>) provided by the user. " << std::endl;
        std::cout <<"Press 5 for available structuring element variants." << std::endl;
        break;
        case 5:
            std::cout<<"\t AVAILABLE STRUCTURING ELEMENTS:" << std::endl;
        for(int i = 1; i <= 10; i++) {
            std::cout<< "SE_" << i << std::endl;
            printSingleMatrix(MorphologicalBasic::assignNumberToStructuringElement(i));
            std::cout<<"\n";
        }
        std::cout<<"\t HMT:" << std::endl;
        for(int j = 1; j <= 12; j++) {
            std::cout<< "SE_" << j << std::endl;
            printSingleMatrix(MorphologicalBasic::assignNumberToSEHMT(j));
            std::cout<<"\n";
        }
        break;
        case 0:
            std::cout<<"\n ALL COMMANDS:" << std::endl;
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
        std::cout << "--mse, --pmse, --snr, --psnr, --md                        - Multiple similarity commands can be used together to compare images." << std::endl;
        std::cout<< "--cmean --cvariance --cstdev --cvarcoi --casyco --cfsyco --cvarcoii --centropy     - Multiple image characteristic parameters that can be used together to display values." << std::endl;
        std::cout<<"--sedgesharp <value>        - Applies a edge sharpening mask linear image filtration algorithm. The available values are 1, 2, 3. The matrices look as follows:" << std::endl;
        printMatrix(SpatialOperations::h1, SpatialOperations::h2, SpatialOperations::h3);
        std::cout<<"--hpower                                                  - Applies a power density function to the histogram. Gives two outputs: an changed image and an image histogram." <<std::endl;
        std::cout<<"--orosenfeld                                              - Applies a rosenfeld operator non-linear spatial filtration algorithm."<<std::endl;
        std::cout<<"--dilation <structuring_element_number>                   - Applies dilation operation with a given structuring element." << std::endl;
        std::cout <<"--erosion <structuring_element_number>                    - Applies erosion operation with a given structuring element." << std::endl;
        std::cout <<"--opening <structuring_element_number>                    - Applies opening operation with a given structuring element. It is dilated erosion." << std::endl;
        std::cout <<"--closing <structuring_element_number>                    - Applies closing operation with a given structuring element. It is eroded dilation." << std::endl;
        std::cout <<"--hmt <structuring_element_number>                        - Applies hit-or-miss operation with a given structuring element." << std::endl;
        std::cout <<"--thinning                                                - Applies thinning operation. No parameter needed." << std::endl;
        std::cout <<"--rgrowing <x> <y> <threshold>                            - Applies region growing with a <threshold> a seed pixel at (<x>,<y>) provided by the user. " << std::endl;
        std::cout <<"Press 5 while calling help() for available structuring element variants." << std::endl;
        break;
        default:
            std::cout <<"WRONG INPUT. Returning..." << std::endl;
            std::cin.clear();
            break;
    }
}

void CommandLineInterface::printMatrix(int h1[3][3], int h2[3][3], int h3[3][3]) {
    std::cout << "Matrix 1\t\t\tMatrix 2\t\t\tMatrix 3" << std::endl; // Headers for clarity
    for (int i = 0; i < 3; ++i) { // Loop through rows
        for (int j = 0; j < 3; ++j) { // Print row of h1
            std::cout << h1[i][j] << "\t";
        }
        std::cout << "\t"; // Space between matrices
        for (int j = 0; j < 3; ++j) { // Print row of h2
            std::cout << h2[i][j] << "\t";
        }
        std::cout << "\t"; // Space between matrices
        for (int j = 0; j < 3; ++j) { // Print row of h3
            std::cout << h3[i][j] << "\t";
        }
        std::cout << std::endl; // Move to next row
    }
}

#include "CImg.h"
#include <iostream>

#include "CommandLineInterface.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char* argv[]) {
    // // CImg<unsigned char> image2(21, 21, 1, 1, 0); // Initialize a 21x21 image with all pixels set to 0 (black)
    // //  for (int i = 1; i < 21; i++) {
    // //      for(int j = 0; j < 10; j++) {
    // //          image2(10+j, i) = 255; // Set the middle column to 255 (white)
    // //      }
    // //  }
    // image2.save_bmp("image.bmp");
    CommandLineInterface::parseCommand(argc, argv);
    return 0;
}


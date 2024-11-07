#include "CImg.h"
#include <iostream>

#include "CommandLineInterface.h"

using namespace cimg_library;
using namespace std;

int main(int argc, char* argv[]) {
    CommandLineInterface::parseCommand(argc, argv);
    return 0;
}


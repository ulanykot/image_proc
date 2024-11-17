//
// Created by MSI on 29.10.2024.
//

#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H



class CommandLineInterface {
public:
    static void help();
    static void parseCommand(int argc, char* argv[]);
    static void printMatrix(int h1[3][3], int h2[3][3], int h3[3][3]);
};



#endif //COMMANDLINEINTERFACE_H

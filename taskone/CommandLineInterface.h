//
// Created by MSI on 29.10.2024.
//

#ifndef COMMANDLINEINTERFACE_H
#define COMMANDLINEINTERFACE_H



class CommandLineInterface {
public:
    static void help();
    static void parseCommand(int argc, char* argv[]);
};



#endif //COMMANDLINEINTERFACE_H

//
// Created by qj on 24.05.18.
//

#ifndef PROJECT_COMPILER_H
#define PROJECT_COMPILER_H


#include <bitset>
#include <vector>
#include "../structures/Commands.h"

class Compiler {
    static void writeLine(std::ofstream stream, std::string line);
public:
    static void placeholder();
    static std::string getLine(Commands command, std::vector<std::bitset<64>> data);

    static std::stringstream fileToBytes(std::ifstream& input);
};


#endif //PROJECT_COMPILER_H

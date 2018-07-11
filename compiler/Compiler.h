//
// Created by qj on 24.05.18.
//

#ifndef PROJECT_COMPILER_H
#define PROJECT_COMPILER_H


#include <bitset>
#include <vector>
#include "../structures/Commands.h"

class Compiler {
//STATIC FUNCTIONS
    static void writeLine(std::ofstream stream, std::string line);
public:
    static void placeholder();
    static std::string getLine(Commands command, std::vector<std::bitset<64>> data);
    static std::stringstream fileToBytes(std::ifstream& input);
    static unsigned long hashVariable(std::string var);
//COMPILER LOGIC
private:
	std::ifstream input;
public:
	Compiler(std::string filename);
};


#endif //PROJECT_COMPILER_H

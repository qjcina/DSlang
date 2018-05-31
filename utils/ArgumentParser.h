//
// Created by qj on 21.05.18.
//

#ifndef PROJECT_ARGUMENTPARSER_H
#define PROJECT_ARGUMENTPARSER_H


#include <vector>

class ArgumentParser {
    std::vector<char> _arguments;
    std::string filename;
public:
    ArgumentParser(int argc, char** argv);
    bool isArg(char arg)const;
    std::string getFilename();
};


#endif //PROJECT_ARGUMENTPARSER_H

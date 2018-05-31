//
// Created by qj on 21.05.18.
//

#include <stdexcept>
#include <algorithm>
#include "ArgumentParser.h"


ArgumentParser::ArgumentParser(int argc, char **argv) {
    for (int i = 1; i < argc; ++i) {
        if(argv[i][0]=='-')
            if(argv[i][1]!='f')
                _arguments.push_back(argv[i][1]);
            else{
                filename = std::string(argv[i]);
                filename.erase(0,2);
            }
        else
            throw std::invalid_argument(argv[i]);
    }
    if(filename.empty())
        filename = std::string("in.ds");
}

bool ArgumentParser::isArg(char arg)const {
    return std::find(_arguments.begin(), _arguments.end(), arg)!=_arguments.end();
}

std::string ArgumentParser::getFilename() {
    return this->filename;
}

//
// Created by qj on 21.05.18.
//
#include <stdexcept>
#include <iostream>
#include "utils/ArgumentParser.h"
#include "utils/Settings.h"

int main(int argc, char** argv){
    ArgumentParser* args;
    try {
        args = new ArgumentParser(argc, argv);
    } catch (std::invalid_argument& e){
        std::cout<<"Invalid argument! Arg: "<< e.what() <<std::endl;
    }
    const Settings* settings = new Settings(args);
    return 0;
}
//
// Created by qj on 21.05.18.
//
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "utils/ArgumentParser.h"
#include "utils/Settings.h"
#include "vm/VirtualMachine.h"
#include "compiler/Compiler.h"

int main(int argc, char** argv){
    ArgumentParser* args = nullptr;
    try {
        args = new ArgumentParser(argc, argv);
    } catch (std::invalid_argument& e){
        std::cout<<"Invalid argument! Arg: "<< e.what() <<std::endl;
        exit(-2);
    }
    if(args->isArg('c'))
        Compiler::placeholder();
    //const Settings* settings = new Settings(args);
    VirtualMachine* vm;
    if(args->isArg('i'))
        vm = new VirtualMachine();
    else {
        if(args->isArg('C')){
            std::ifstream inputStream(args->getFilename());
            vm = new VirtualMachine(new std::istringstream(Compiler::fileToBytes(inputStream).str()));
        } else {
            auto const filename = args->getFilename();
            vm = new VirtualMachine(filename);
        }
    }
    vm->run();

    return 0;
}
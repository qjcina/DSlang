//
// Created by qj on 21.05.18.
//
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include "utils/Constants.h"
#include "utils/ArgumentParser.h"
#include "vm/VirtualMachine.h"
#include "compiler/Compiler.h"

[[ noreturn ]] void printUsage(char* name){
    std::cout<<"Usage: \n"
             << name <<" -f<filename>\n"
             << "Use: -c for placeholder program\n"
             << "     -C for compiling from vm asm\n"
             << "     -i basic interactive mode\n"
             << "     -h for help\n"
             << "     -v for version\n"
             << "Example: " << name << " -fin.asm -C";
    exit(-2);

}

int main(int argc, char** argv){
    ArgumentParser* args = nullptr;
    try {
        args = new ArgumentParser(argc, argv);
    } catch (std::invalid_argument& e){
        std::cout<<"Invalid argument! Arg: "<< e.what() <<std::endl;
        printUsage(argv[0]);
    }
    if(args->isArg('c'))
        printUsage(argv[0]);
    if(args->isArg('c'))
        Compiler::placeholder();
    if(args->isArg('v'))
        std::cout<<"Version: "<<VERSION_MAJOR<<"."<<VERSION_MINOR<<"."<<VERSION_GIT<<std::endl;
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
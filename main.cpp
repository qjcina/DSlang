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
             << "Use: -c compliling\n"
             << "     -C for compiling from vm asm\n"
             << "     -i basic interactive mode\n"
             << "     -h for help\n"
             << "     -v for version\n"
             << "Example: " << name << " -fin.asm -C\n";
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
    if(args->isArg('h'))
        printUsage(argv[0]);
	if (args->isArg('c')) {
		auto compilerInstance = new Compiler(args->getFilename());
	}
    if(args->isArg('v'))
        std::cout<<"Version: "<<VERSION_MAJOR<<"."<<VERSION_MINOR<<"."<<VERSION_GIT<<std::endl;
    VirtualMachine* vm;
    if(!args->isArg('r')) {
        //Standard mode console
        if (args->isArg('i'))
            //Interactive mode
            vm = new VirtualMachine();
        else {
            //Compiled mode
            if (args->isArg('C')) {
                //Compile DS-asm
                std::ifstream inputStream(args->getFilename());
				if (!inputStream.is_open()) {
					std::cout << "Invalid file! Arg: " << std::endl;
					printUsage(argv[0]);
				}
                vm = new VirtualMachine(new std::istringstream(Compiler::fileToBytes(inputStream).str()));
            } else {
                //Read bytecode
                auto const filename = args->getFilename();
                vm = new VirtualMachine(filename);
            }
        }
        vm->run();
    } else {
        //TODO UI with interactive commands (reading, compliling etc.)
    }

    return 0;
}
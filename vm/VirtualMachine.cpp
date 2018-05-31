//
// Created by qj on 22.05.18.
//

#include <sstream>
#include <iterator>
#include <iostream>
#include <cstring>
#include <limits>
#include "VirtualMachine.h"
#include "../structures/Commands.h"

/*
 * Main virtual machine running loop.
 * Returns:
 * *    0   - success
 * *    -1  - failure
 */
int VirtualMachine::run() {
    std::string line;
    while (std::getline((*inputStream), line)) {
        long unsigned readValue;
        std::stringstream lineStream(line);
        std::vector<long unsigned> lineValues;
        while (lineStream >> std::hex >> readValue) {
            lineValues.push_back(readValue);
        }
        action(lineValues);
        lineNumber++;
        if(line.empty())
            break;
    }
    return 0;
}

VirtualMachine::VirtualMachine(std::string const &filename, bool run) {
    lineNumber = 1;
    inputStream = new std::ifstream(filename);
    if (inputStream->fail())
        std::cout << "Error reading input from " << filename << "." << std::endl
                  << "Info: " << strerror(errno) << std::endl;
    if (run)
        this->run();
}

VirtualMachine::VirtualMachine(std::istream* input, bool run) {
    lineNumber = 1;
    inputStream = input;
    if (run)
        this->run();
}

VirtualMachine::VirtualMachine(bool run) {
    lineNumber = 1;
    inputStream = &std::cin;
    if (run)
        this->run();
}

void VirtualMachine::printError(std::string error) {
    std::cout << "Error: " << error;
    if (lineNumber+codeLine >= 0)
        std::cout << " at line " << (codeLine == 0? lineNumber:codeLine);
    std::cout << std::endl;
}

void VirtualMachine::action(std::vector<long unsigned> const &line) {
    if(line.empty())
        return;
    switch (line.at(0)) {
        case Commands::DUB:
            valsStack.push(valsStack.top());
            break;
        case Commands::JEQ:
        case Commands::JNE:
        case Commands::JGE:
        case Commands::JGR:
        case Commands::JLE:
        case Commands::JLS:
            jumpIf((Commands) line.at(0), line.at(1), line.at(2));
            break;
        case Commands::JMP:
            jump(line.at(1));
            break;
        case Commands::SUB:
        case Commands::ADD:
        case Commands::MUL:
        case Commands::DIV:
            operation((Commands) line.at(0));
            break;
        case Commands::POP:
            std::cout << valsStack.top()->getVal().to_ullong();
            break;
        case Commands::PUS:
            pushStack(line.at(1), Element::Types::smallInt);
            break;
        case Commands::RRR:
            exit(0);
        default:
            printError("Command error");
    }
}

void VirtualMachine::jumpIf(Commands command, unsigned long line, const unsigned long & condition){
    long long top = popStack()->getVal().to_ullong();
    switch (command){
        case JEQ: if(top==condition) jump(line); break;
        case JNE: if(top==condition) jump(line); break;
        case JGR: if(top==condition) jump(line); break;
        case JGE: if(top==condition) jump(line); break;
        case JLS: if(top==condition) jump(line); break;
        case JLE: if(top==condition) jump(line); break;
    }
}

void VirtualMachine::jump(unsigned long line){
    --line;
    try {
        int seek = seekMap.at(static_cast<const int &>(line));
        inputStream->seekg(seek);
        lineNumber = line;
    } catch(std::out_of_range& e) {
        if (line < lineNumber) {
            inputStream->seekg(std::ios::beg);
            lineNumber = 1;
        }
        while (lineNumber != line) {
            inputStream->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            lineNumber++;
        }
        seekMap.insert(std::make_pair(line, inputStream->tellg()));
    }
}

Element *VirtualMachine::popStack() {
    if (valsStack.empty()) {
        printError("Stack fault");
        exit(-1);
    }
    auto var = valsStack.top();
    valsStack.pop();
    return var;
}

void VirtualMachine::pushStack(long unsigned arg, Element::Types type) {
    valsStack.push(new Element(arg, type));
}

void VirtualMachine::operation(Commands type) {
    Element *a = popStack(), *b = popStack();
    if (a->getType() == b->getType() && a->getType() == Element::Types::smallInt) {
        long long val = 0;
        switch (type) {
            case ADD:
                val = a->getVal().to_ullong() + b->getVal().to_ullong();
                break;
            case SUB:
                val = a->getVal().to_ullong() - b->getVal().to_ullong();
                break;
            case MUL:
                val = a->getVal().to_ullong() * b->getVal().to_ullong();
                break;
            case DIV:
                val = a->getVal().to_ullong() / b->getVal().to_ullong();
                break;
            default:
                printError("Operation error");
        }
        valsStack.push(new Element(val, Element::Types::smallInt));
    }
    delete a;
    delete b;

}



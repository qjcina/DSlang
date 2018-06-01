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
        unsigned long long readValue;
        std::stringstream lineStream(line);
        std::vector<unsigned long long> lineValues;
        while (lineStream >> std::hex >> readValue) {
            lineValues.push_back(readValue);
        }
        action(lineValues);
        lineNumber++;
        if (line.empty())
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

VirtualMachine::VirtualMachine(std::istream *input, bool run) {
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
    if (lineNumber + codeLine >= 0)
        std::cout << " at line " << (codeLine == 0 ? lineNumber : codeLine);
    std::cout << std::endl;
}

void VirtualMachine::action(std::vector<unsigned long long> const &line) {
    if (line.empty())
        return;
    switch (line.at(0)) {
        case Commands::GEC:
            getCachePointer();
            break;
        case Commands::SVM:
        case Commands::RVM:
            handleMemory((Commands) line.at(0), line.at(1));
            break;
        case Commands::SVC:
        case Commands::RVC:
            handleCache((Commands) line.at(0), line.at(1));
            break;
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
            std::cout <<
                      (valsStack.top()->getType()==Element::Types::Float64?
                       valsStack.top()->getFloat() : valsStack.top()->getInteger())
                      << "\n";
            break;
        case Commands::PUS:
            handlePush(line);
            break;
        case Commands::RRR:
            exit(0);
        default:
            printError("Command error");
    }
}

void VirtualMachine::handlePush(const std::vector<unsigned long long> &line) {
    unsigned type;
    try {
        type = (unsigned int) line.at(2);
    } catch (std::out_of_range &e) {
        type = 0;
    }
    pushStack(line.at(1), static_cast<Element::Types>(type));

}

void VirtualMachine::getCachePointer() {
    for (int i = 0; i < 128; ++i) {
        if (cache[i] == nullptr) {
            pushStack(i, Element::Types::Int64);
            return;
        }
    }
    pushStack(128, Element::Types::Int64);
}

void VirtualMachine::handleMemory(Commands command, unsigned long long variableHash) {
    if (command == Commands::SVM) {
        Element *var = popStack();
        memory.emplace(std::make_pair(variableHash, var));
    } else {
        auto data = memory.find(variableHash);
        valsStack.push(data->second);
        memory.erase(data);
    }
}

void VirtualMachine::handleCache(Commands command, unsigned long long address) {
    if (address >= 128) {
        printError("Cache error");
        return;
    }
    if (command == Commands::SVC) {
        Element *var = popStack();
        cache[address] = var;
    } else {
        valsStack.push(cache[address]);
        cache[address] = nullptr;
    }
}

void VirtualMachine::jumpIf(Commands command, unsigned long long line, const unsigned long long &condition) {
    long long top = popStack()->getVal().to_ullong();
    switch (command) {
        case JEQ:
            if (top == condition) jump(line);
            break;
        case JNE:
            if (top == condition) jump(line);
            break;
        case JGR:
            if (top == condition) jump(line);
            break;
        case JGE:
            if (top == condition) jump(line);
            break;
        case JLS:
            if (top == condition) jump(line);
            break;
        case JLE:
            if (top == condition) jump(line);
            break;
    }
}

void VirtualMachine::jump(unsigned long long line) {
    --line;
    try {
        int seek = seekMap.at(static_cast<const int &>(line));
        inputStream->seekg(seek);
        lineNumber = line;
    } catch (std::out_of_range &e) {
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

template<typename T>
void VirtualMachine::pushStack(T arg, Element::Types type) {
    valsStack.push(
            new Element(
                    Element::cast<T>(arg), type
            )
    );
}

void VirtualMachine::operation(Commands type) {
    Element *a = popStack(), *b = popStack();
    if (a->getType() == b->getType() && a->getType() == Element::Types::Int64) {
        long long val = 0;
        switch (type) {
            case ADD:
                val = a->getInteger() + b->getInteger();
                break;
            case SUB:
                val = a->getInteger() - b->getInteger();
                break;
            case MUL:
                val = a->getInteger() * b->getInteger();
                break;
            case DIV:
                val = a->getInteger() / b->getInteger();
                break;
            default:
                printError("Operation error");
        }
        pushStack(val, Element::Types::Int64);
    } else if (a->getType() == b->getType() && a->getType() == Element::Types::Float64) {
        double val = 0;
        switch (type) {
            case ADD:
                val = a->getFloat() + b->getFloat();
                break;
            case SUB:
                val = a->getFloat() - b->getFloat();
                break;
            case MUL:
                val = a->getFloat() * b->getFloat();
                break;
            case DIV:
                val = a->getFloat() / b->getFloat();
                break;
            default:
                printError("Operation error");
        }
        pushStack(Element::cast<double>(val), Element::Types::Float64);
    } else {
        printError("Incompatible types");
    }

    delete a;
    delete b;

}



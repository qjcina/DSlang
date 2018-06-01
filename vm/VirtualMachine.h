//
// Created by qj on 22.05.18.
//

#ifndef PROJECT_VIRTUALMACHINE_H
#define PROJECT_VIRTUALMACHINE_H


#include <fstream>
#include <vector>
#include <stack>
#include <bitset>
#include <map>
#include "Element.h"
#include "../structures/Commands.h"

class VirtualMachine {
    //Data sector
    std::stack<Element*> valsStack;
    std::map<int, int> seekMap; //map of jumps
    Element* cache[128]; //quick memory, but max 128 elements
    std::map<unsigned long long, Element*> memory; //slower memory
    //Utilities
    std::istream* inputStream; //code input stream
    int codeLine; //line in code (NYI)
    unsigned long long lineNumber; //vm-asm line number

    Element* popStack();
    void printError(std::string error);
    void operation(Commands type);
    void action(const std::vector<unsigned long long> &line);
    template <typename T>
    void pushStack(T arg, Element::Types type);
    void jumpIf(Commands command, unsigned long long line, const unsigned long long &condition);
    void jump(unsigned long long line);
    void handleCache(Commands command, unsigned long long address);
    void handleMemory(Commands command, unsigned long long variableHash);
    void getCachePointer();
    void handlePush(const std::vector<unsigned long long> &line);
public:
    explicit VirtualMachine(bool run = false);
    explicit VirtualMachine(std::istream *input, bool run= false);
    explicit VirtualMachine(std::string const& filename, bool run = false);
    int run();



};


#endif //PROJECT_VIRTUALMACHINE_H

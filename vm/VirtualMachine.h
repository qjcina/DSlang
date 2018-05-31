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
    std::istream* inputStream;
    int codeLine;
    unsigned long lineNumber;
    std::stack<Element*> valsStack;
    Element* popStack();
    std::map<int, int> seekMap;

    void printError(std::string error);
    void operation(Commands type);
    void action(const std::vector<long unsigned> &line);
    void pushStack(unsigned long arg, Element::Types type);
    void jumpIf(Commands command, unsigned long line, const unsigned long &condition);
    void jump(unsigned long line);
public:
    explicit VirtualMachine(bool run = false);
    explicit VirtualMachine(std::istream *input, bool run= false);
    explicit VirtualMachine(std::string const& filename, bool run = false);
    int run();
};


#endif //PROJECT_VIRTUALMACHINE_H

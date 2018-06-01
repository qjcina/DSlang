//
// Created by qj on 22.05.18.
//

#ifndef PROJECT_COMMANDS_H
#define PROJECT_COMMANDS_H

enum Commands{
    DUB = 0x01,
    ADD, //ADD
    SUB, //SUBSTRACT
    MUL, //MULTIPLY
    DIV, //DIVIDE
    PUS, //PUSH
    POP, //POP
    JMP, //JUMP
    JEQ, //JUMP WHEN EQUAL
    JNE, //JUMP NOT EQUAL
    JGR, //JUMP GREATER
    JGE, //JUMP GREATER EQUAL
    JLS, //JUMP LESSER
    JLE, //JUMP LESSER EQUAL
    SGT, //START GREEN THREAD
    SVM, //SAVE VARIABLE TO MAP
    RVM, //READ VARIABLE FROM MAP
    SVC, //SAVE VARIABLE TO CACHE
    RVC, //READ VARIABLE FROM CACHE
    GEC, //GET EMPTY CACHE ADDRESS
    CST, //CAST FORMATS
    RRR = 0xFF
};
#include <algorithm>
#include <string>
class CommandsUtils {
    inline constexpr static const char* commands[255]{"DUB",
                                               "ADD",
                                               "SUB",
                                               "MUL",
                                               "DIV",
                                               "PUS",
                                               "POP",
                                               "JMP",
                                               "JEQ",
                                               "JNE",
                                               "JGR",
                                               "JGE",
                                               "JLS",
                                               "JLE",
                                               "SGT",
                                               "SVM",
                                               "RVM",
                                               "SVC",
                                               "RVC",
                                               "GEC",
                                               "CST",

    };
public:
    static short valueOf(const std::string &name) {
        if(name == "RRR")
            return 0xFF;
        for (short i = 0; i < 255; ++i) {
            if(std::string(commands[i])==name)
                return static_cast<short>(i + 1);
        }
        return -1;
    }
};
#endif //PROJECT_COMMANDS_H

//
// Created by qj on 30.05.18.
//

#ifndef PROJECT_ELEMENT_H
#define PROJECT_ELEMENT_H


#include <bitset>


class Element {
public:
    enum Types{
        smallInt
    };

    Element(std::bitset<64> value, Element::Types type);

private:

    std::bitset<64> val;
    Types const type;
public:
    std::bitset<64> getVal();

    Types getType();
};




#endif //PROJECT_ELEMENT_H

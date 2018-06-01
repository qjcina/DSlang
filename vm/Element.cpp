//
// Created by qj on 30.05.18.
//

#include "Element.h"

Element::Element(unsigned long long value, Element::Types type):
        val(value), type(type) {
}


std::bitset<64> Element::getVal() {
    return val;
}

Element::Types Element::getType() {
    return this->type;
}

double Element::getFloat() {
    return *reinterpret_cast<double *>(&val);
}

long long Element::getInteger() {
    return *reinterpret_cast<long long *>(&val);
}







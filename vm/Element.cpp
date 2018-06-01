//
// Created by qj on 30.05.18.
//

#include <cmath>
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

void Element::castTo(Element::Types type) {
    switch(type){
        case Int64: if(this->type != Int64) toInteger(); break;
        case Float64: if(this->type != Float64)  toFloat(); break;
    }

}

void Element::toFloat() {
    double value = getInteger();
    type = Float64;
    val = cast<double>(value);
}

void Element::toInteger() {
    double value = getFloat();
    type = Int64;
    auto intValue = static_cast<long long>(round(value));
    val = cast<long long>(intValue);
}







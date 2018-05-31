//
// Created by qj on 30.05.18.
//

#include "Element.h"

Element::Element(std::bitset<64> value, Element::Types type):
        val(value), type(type) {

}

std::bitset<64> Element::getVal() {
    return val;
}

Element::Types Element::getType() {
    return this->type;
}

//
// Created by qj on 30.05.18.
//

#ifndef PROJECT_ELEMENT_H
#define PROJECT_ELEMENT_H


#include <bitset>

class Element {
public:
    enum Types{
        Int64,Float64
    };
private:
    std::bitset<64> val;
    Types type;
    void toFloat();
    void toInteger();
public:
    Element(unsigned long long value, Element::Types type);
    std::bitset<64> getVal();
    Types getType();
    double getFloat();
    void castTo(Element::Types type);
    long long getInteger();
    template <typename T>
    static unsigned long long cast(T value){
        return *reinterpret_cast<unsigned long long*>(&value);
    };
};




#endif //PROJECT_ELEMENT_H

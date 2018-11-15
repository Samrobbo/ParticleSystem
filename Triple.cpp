//
// Created by sam_r on 15/11/2018.
//


#include "Triple.h"

Triple::Triple() {
    this->first = 0;
    this->second = 0;
    this->third = 0;
}

Triple::Triple(double a, double b, double c) {
    this->first = a;
    this->second = b;
    this->third = c;
}

Triple Triple::operator+ (const Triple& t) const {
    Triple result;
    result.first = (this->first + t.first);
    result.second = (this->second + t.second);
    result.third = (this->third + t.third);
    return result;
}

Triple Triple::operator* (const int scalar) const {
    Triple result;
    result.first = (this->first * scalar);
    result.second = (this->second * scalar);
    result.third = (this->third * scalar);
    return result;
}
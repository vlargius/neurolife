#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include "dimentions.h"


namespace trd {

template<class UnitType>
const char* type_to_string(const UnitType&) {
    return "[units]";
}

template<>
const char* type_to_string(const Second&) {
    return "[s]";
}

template<>
const char* type_to_string(const Meter&) {
    return "[m]";
}

template<>
const char* type_to_string(const Speed&) {
    return "[m/s]";
}


template<class UnitType>
std::ostream& operator<<(std::ostream& os, const Value<UnitType>& value) {
    os << value.value << type_to_string(value);
    return os;
}

template<class UnitType>
std::istream& operator>>(std::istream& is, Value<UnitType>& value) {
    is >> value.value;
    const char* typeStr = type_to_string(value);
    char c;
    int i = 0;
    int maxLen = strlen(typeStr);
    while(is.get(c) && c != ']' && i < maxLen) {
        if (c != typeStr[i])
            throw std::invalid_argument("wrong unit dimention");
        ++i;
    }
    return is;
}

}
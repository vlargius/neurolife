#pragma once

#include <iostream>
#include <string>
#include <cstring>

#include "dimentions.h"


template<class UnitType>
inline const char* type_to_string(const UnitType&) {
    return "[units]";
}

template<>
inline  const char* type_to_string(const Second&) {
    return "[s]";
}

template<>
inline  const char* type_to_string(const Meter&) {
    return "[m]";
}

template<>
inline  const char* type_to_string(const MeterPerSec&) {
    return "[m/s]";
}


template<class UnitType>
inline  std::ostream& operator<<(std::ostream& os, const trd::Value<UnitType>& value) {
    return os << value.value << type_to_string(value);
}

template<class UnitType>
inline  std::istream& operator>>(std::istream& is, trd::Value<UnitType>& value) {
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

template<class UnitType>
std::ostream& operator<<(std::ostream& os, const trd::Vec2<UnitType>& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}
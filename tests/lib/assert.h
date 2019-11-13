#pragma once
/*
asserter - checks various conditions and throw assert object if condition is fulfilled
*/
#include <stdexcept>
#include <string>
#include <sstream>
#include <limits>

namespace NTest{
struct AssertException : public std::logic_error {
    AssertException(const std::string& msg):
        std::logic_error(msg) {}
};
}

inline void Assert(bool value, const std::string& message = "assertation failed") {
    if (!value) {
        throw NTest::AssertException(message);
    }
}

template<class Type1, class Type2>
void AssertEqual(const Type1& value, const Type2& desired, const std::string& parname = "") {
    if (value != desired) {
        std::stringstream ss;
        ss << (!parname.empty() ? parname : "value")
            << ": " << value << " != " << desired;
        throw NTest::AssertException(ss.str());
    }
}

template<class Type1, class Type2>
void AssertNotEqual(const Type1& value, const Type2& desired, const std::string& parname = "") {
    if (value == desired) {
        std::stringstream ss;
        ss << (!parname.empty() ? parname : "value")
            << ": " << value << " != " << desired;
        throw NTest::AssertException(ss.str());
    }
}

template<class Type1, class Type2>
void AssertNear(const Type1& value, const Type2& desired, const std::string& parname = "",
    const Type1& eps = std::numeric_limits<Type1>::epsilon()) {
    if (std::abs((Type1)value - (Type1)desired) > eps) {
        std::stringstream ss;
        ss << (!parname.empty() ? parname : "value")
            << ": " << value << " != " << desired << " difference is: " << value - desired;
        throw NTest::AssertException(ss.str());
    }
}
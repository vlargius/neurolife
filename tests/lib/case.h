#pragma once
#include <string>

#include "assert.h"

namespace NTest {

class Case {
public:
    Case(const std::string& name):
        name(name) {}
    virtual ~Case() = default;

    virtual void run() = 0;

    virtual void formatRun() final;
protected:
    const std::string name;
};
}  // namespace NTest

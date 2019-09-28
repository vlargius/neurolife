#pragma once
#include <string>


namespace NTest {

class Case {
public:
    Case(const std::string& name):
        name(name) {}
    virtual ~Case() {}

    virtual void run() = 0;

    virtual void formatRun() final;
protected:
    const std::string name;
};
}  // namespace NTest

using NTestCase = NTest::Case;
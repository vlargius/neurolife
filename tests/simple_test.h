#pragma once

#include "lib/train.h"

using namespace NTest;
class SimpleTest : public Case {
public:
    SimpleTest():
        Case("Simple test") {}

    void run() override {
        std::cout << "test" << std::endl;
    }
};

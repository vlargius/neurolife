#pragma once

#include "lib/train.h"

class SimpleTest : public NTestCase {
public:
    SimpleTest():
        NTestCase("Simple test") {}

    void run() override {
        std::cout << "test" << std::endl;
    }
};

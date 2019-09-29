#pragma once
#include <iostream>
#include <vector>

#include "case.h"


namespace NTest {

class Train {
public:

    static Train& get();
    ~Train();

    void run();
    void addTest(Case* test);

private:
    std::vector<Case*> cases;

    Train() = default;
    Train(const Train&) = delete;
    Train& operator=(const Train&) = delete;
};
}

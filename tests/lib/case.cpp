#include "case.h"
#include <iostream>

namespace NTest {
    void Case::formatRun() {
        std::cout << "Test: " <<  name << std::endl
            << "-------------------------------------------" << std::endl;
        run();
        std::cout << std::endl << std::endl;
    }
}
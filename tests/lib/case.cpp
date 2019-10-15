#include "case.h"

#include <iostream>


static const char* red   {"\033[0;31m"};
static const char* green {"\x1B[32m"};
static const char* reset {"\x1B[0m"};

namespace NTest {
    void Case::formatRun() {
        std::cout << "Test: " <<  name << std::endl
            << "-------------------------------------------" << std::endl;
        try {
            run();
            std::cout << green << "Done" << reset;
        } catch (const AssertException& a) {
            std::cout << red << "Failed" << reset << ": " << a.what();

        } catch (const std::exception& e) {
            std::cout << red << "Failed" << reset << ": " << e.what();
        }
        std::cout << std::endl << std::endl;
    }
}
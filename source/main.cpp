/*
entering point of neurolife project
*/

#include <iostream>
#include <string>

#include "lib/dimentions.h"

using namespace trd;

int main(int argc, char*argv[])
try {

    Meter l(5);
    Second t(10);

    Speed a = l / t;
    Acceleration acc = a / t;

    std::cout << a.value << std::endl;
    return 0;
} catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "something bad has happened" << std::endl;
}
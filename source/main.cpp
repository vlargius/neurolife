/*
entering point of neurolife project
*/

#include <iostream>
#include <string>

#include "actor.h"


int main(int argc, char*argv[])
try {
    Actor a;

    Actor b(Position{Meter(523), Meter(32)});

    std::cout << a << " " << b;

    return 0;
} catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "something bad has happened" << std::endl;
}
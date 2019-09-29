/*
entering point of neurolife project
*/

#include <iostream>
#include <string>

#include "lib/dimentions.h"
#include "lib/print_dimentions.h"

using namespace trd;

int main(int argc, char*argv[])
try {


    return 0;
} catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "something bad has happened" << std::endl;
}
/*
entering point of neurolife project
*/

#include <iostream>
#include <string>

int main(int argc, char*argv[])
try {
    std::cout << "hello" << std::endl;
    return 0;
} catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "something bad has happened" << std::endl;
}
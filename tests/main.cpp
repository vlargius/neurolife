/*
testing environment for neurolife project
*/

#include <iostream>

#include "lib/train.h"
#include "simple_test.h"


int main(int argc, char*argv[])
try {
    NTest::Train& train = NTest::Train::get();
    train.addTest(new SimpleTest());
    train.run();
}
catch (const std::exception& e) {
    std::cerr << "there was an error: " << e.what() << std::endl;
}
catch (...) {
    std::cerr << "something unexpected has happened" << std::endl;
}
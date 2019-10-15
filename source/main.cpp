/*
entering point of neurolife project
*/

#include <iostream>
#include <string>
#include <memory>

#include "updater.h"


int main(int argc, char*argv[])
try {
    struct data : IUpdatable {
        void tick(Second dt) override {
            std::cout << "hello\n";
        }
    } inst;
    Updater updater(&inst);

    Updater::RunConfig config;
    config.dt = Second(1);
    config.ttl = 80;

    updater.run(config);

    return 0;
} catch (const std::exception& e) {
    std::cerr << "error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "something bad has happened" << std::endl;
}
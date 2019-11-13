/*
entering point of neurolife project
*/

#include <time.h>
#include <iostream>
#include <memory>
#include <string>

#include "manager.h"

int main(int argc, char *argv[]) try {
    World::CreateConf w_conf{
        .size = {Meter(100), Meter(100)},
        .actors_count = 10};

    GuiRender::CreateConf r_conf{.outBox = {1020, 980}};

    Manager manager(w_conf, Second(.0002), r_conf);
    Updater updater(&manager);

    Updater::RunConfig config{.fps = Hertz(50), .ttl = 10000};

    updater.run(config);

    return 0;
} catch (const std::exception &e) {
    std::cerr << "error: " << e.what() << std::endl;
} catch (...) {
    std::cerr << "something bad has happened" << std::endl;
}
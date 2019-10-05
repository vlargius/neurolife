#pragma once
/*
updater system for working with units
*/

#include <memory>

#include "world.h"

struct Updater {
    std::shared_ptr<World> world;

    void tick(float dt);
};
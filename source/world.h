#pragma once
/*
main container for actors
*/

#include <vector>
#include <string>

#include "lib/dimentions.h"
#include "actor.h"

struct Box {
    Meter height;
    Meter width;
};

struct World {
    Box size;

    std::vector<Actor> actors;
};

std::ostream& operator<<(std::ostream&, const World&);
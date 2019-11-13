#pragma once
/*
base actor unit class that represent a victim or a predator
*/

#include <iostream>

#include "lib/dimentions.h"


struct Actor {
public:
    Position pos;
    Velocity vel;
    Force force;
    Kilogram mass;

    Actor():
        pos(),
        vel(),
        force() {}

    explicit Actor(const Position& pos, const Kilogram& mass):
        pos(pos),
        mass(mass) {}

    Meter distance(const Actor& other);

};

std::ostream& operator<<(std::ostream&, const Actor&);
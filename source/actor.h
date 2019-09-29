#pragma once
/*
base actor unit class that represent a victim or a predator
*/

#include <iostream>

#include "lib/dimentions.h"


struct Position {
    Meter x;
    Meter y;
};

std::ostream& operator<<(std::ostream&, const Position&);

struct Actor {
public:
    Position pos;

    Actor():
        pos() {}

    Actor(const Position& pos):
        pos(pos) {}

};

std::ostream& operator<<(std::ostream&, const Actor&);
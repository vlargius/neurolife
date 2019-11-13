#pragma once
/*
main container for actors
*/

#include <vector>
#include <string>

#include "lib/dimentions.h"
#include "actor.h"

template<class T>
struct Rect {
    T width;
    T height;
};
using MeterRect = Rect<Meter>;
using IntRect = Rect<int>;

template<class T>
bool is_in(T val, T min, T max) {
    return val > min && val < max;
}

struct World {
    struct CreateConf{
        MeterRect size = {Meter(10), Meter(10)};
        int actors_count = 1;
    };

    World(const CreateConf& conf);

    bool isIn(const Actor& actor);

    Velocity getNormalCollision(const Actor& actor);
    Force getNormalForce(const Actor& actor);

    MeterRect size;
    std::vector<Actor> actors;
};

std::ostream& operator<<(std::ostream&, const World&);
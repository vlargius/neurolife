#include "world.h"
#include <algorithm>

World::World(const World::CreateConf& conf) :
    size(conf.size) {
    for (int i = 0; i < conf.actors_count; ++i) {
        Position randPos = {
            Meter(rand() % (int)to_double(size.width / 10) + (int)to_double(size.width) / 2),
            Meter(rand() % (int)to_double(size.height / 10) + (int)to_double(size.height) / 2)};
        auto actor = Actor(randPos, Kilogram(10));
        // actor.vel = Velocity({MeterPerSec(rand() % 10), MeterPerSec(rand() % 10)});
        actors.push_back(actor);
    }
    actors.back().mass = Kilogram(10000);
}

bool World::isIn(const Actor& actor) {
    return is_in(actor.pos.x, Meter(0), size.width) && is_in(actor.pos.y, Meter(0), size.height);
}

Velocity World::getNormalCollision(const Actor& actor) {
    const Velocity down = {MeterPerSec(0), MeterPerSec(1)};
    const Velocity up = {MeterPerSec(0), MeterPerSec(-1)};
    const Velocity left = {MeterPerSec(-1), MeterPerSec(0)};
    const Velocity right = {MeterPerSec(1), MeterPerSec(0)};

    const Meter u = actor.pos.y;
    const Meter d = size.height - actor.pos.y;
    const Meter l = actor.pos.x;
    const Meter r = size.width - actor.pos.x;

    Meter dist = std::min({u, d, l, r});

    if (dist == u)
        return down;
    if (dist == d)
        return up;
    if (dist == l)
        return right;
    if (dist == r)
        return left;

    return Velocity();
}

Force World::getNormalForce(const Actor& actor) {
    const Force down = {Newton(0), Newton(1)};
    const Force up = {Newton(0), Newton(-1)};
    const Force left = {Newton(-1), Newton(0)};
    const Force right = {Newton(1), Newton(0)};

    const Meter u = actor.pos.y;
    const Meter d = size.height - actor.pos.y;
    const Meter l = actor.pos.x;
    const Meter r = size.width - actor.pos.x;

    Meter dist = std::min({u, d, l, r});

    if (dist == u)
        return down;
    if (dist == d)
        return up;
    if (dist == l)
        return right;
    if (dist == r)
        return left;

    return Force();
}

std::ostream& operator<<(std::ostream& os, const World& world) {
    for (const Actor& actor : world.actors) {
        os << actor << std::endl;
    }
    return os;
}
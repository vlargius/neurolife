#pragma once

#include "lib/train.h"
#include "../source/actor.h"


using namespace NTest;

class ActorTest : public Case {
public:
    ActorTest():
        Case("Actor test") {}

    void run() override {
        Position pos{Meter(123.34), Meter(23)};
        Kilogram mass{1.0};
        Actor a(pos, mass);

        Assert(a.pos.x == pos.x && a.pos.y == pos.y && a.mass == mass,
            "Copy constructor failed");
    }
};

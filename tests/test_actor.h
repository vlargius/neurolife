#pragma once

#include "lib/train.h"
#include "../source/actor.h"


class ActorTest : public NTestCase {
public:
    ActorTest():
        NTestCase("Actor test") {}

    void run() override {
        Position pos{Meter(123.34), Meter(23)};
        Actor a(pos);

        if (a.pos.x == pos.x && a.pos.y == pos.y) {
            std::cout << "done" << std::endl;
        } else {
            std::cout << "failed" << std::endl;
        }
    }
};

#pragma once

#include <thread>

#include "lib/train.h"
#include "../source/updater.h"

using namespace std::chrono;
using namespace NTest;

using chrono_time_point = std::chrono::system_clock::time_point;

class UpdaterTest : public Case {
public:
    UpdaterTest():
        Case("Updater test") {}

    void run() override {
        static int ticks = 0;
        struct testInst : IUpdatable {
            void tick(Second dt) {
                ++ticks;
                std::this_thread::sleep_for(10ms);
            }
        } inst;

        const int stepCount = 10;
        const Second dt(0.04);

        Updater updater(&inst);

        Updater::RunConfig conf {
            .fps = Hertz(25),
            .ttl = stepCount,
            .throttle=false
        };

        chrono_time_point start = std::chrono::system_clock::now();
        updater.run(conf);
        chrono_time_point end = std::chrono::system_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / 1000.;


        AssertEqual(ticks, stepCount, "ticks");
        AssertNear(duration, to_double(dt)*stepCount, "duration");
    }
};

#pragma once

#include <thread>

#include "lib/train.h"
#include "../source/updater.h"

using namespace std::chrono;

class UpdaterTest : public NTestCase {
public:
    UpdaterTest():
        NTestCase("Updater test") {}

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
            .dt = dt,
            .ttl = stepCount,
            .throttle=false
        };

        std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
        updater.run(conf);
        std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
        double duration = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() / 1000.;


        AssertEqual(ticks, stepCount, "ticks");
        AssertNear(duration, to_double(dt)*stepCount, "duration");
    }
};

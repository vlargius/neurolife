#include "updater.h"

#include <chrono>
#include <thread>
#include <math.h>

#include "lib/print_dimentions.h"

namespace chrono = std::chrono;

Updater::Updater(IUpdatable* inst):
    instance(inst) {}

// - ticks time with set dt up untill ttl is not zero.
// - if calculating is more then set dt calculate new appropriate dt
void Updater::run(const RunConfig& config) {

    ttl = config.ttl;
    constDt = config.dt;

    chrono::system_clock::time_point startAt = chrono::system_clock::now();
    Second dt(constDt);

    for (currStep = 1; currStep <= ttl; ++currStep) {

        tick(dt);

        chrono::system_clock::time_point lastStepTime = chrono::system_clock::now();
        chrono::system_clock::time_point nextStepTime = startAt + chrono::milliseconds(long(to_double(constDt) * currStep*1000));
        if (config.throttle && lastStepTime > nextStepTime)
        {
            double freeze = chrono::duration_cast<chrono::milliseconds>(lastStepTime - nextStepTime).count()*0.001;
            int offsetStep = std::ceil(freeze / to_double(constDt));
            dt = constDt*offsetStep;
            currStep += offsetStep;
        }
        else
        {
            dt = constDt;
        }
        std::this_thread::sleep_until(nextStepTime);
    }
}

void Updater::tick(Second dt) {
    instance->tick(dt);
}
#include "updater.h"

#include <chrono>
#include <thread>
#include <math.h>

#include "lib/print_dimentions.h"

namespace chrono = std::chrono;
using chrono_time_point = chrono::system_clock::time_point;

Updater::Updater(IUpdatable* instance):
    instance(instance) {}

// - ticks time with set dt up untill ttl is not zero.
// - if calculating is more then set dt calculate new appropriate dt
void Updater::run(const RunConfig& config) {
    if (!instance)
        throw std::runtime_error("There is no instance for running updater");

    instance->ttl = config.ttl;
    constDt = 1./config.fps;

    chrono_time_point startAt = chrono::system_clock::now();
    Second dt(constDt);

    for (instance->currStep = 1; instance->running && instance->currStep <= instance->ttl; ++instance->currStep) {

        tick(dt);

        chrono_time_point lastStepTime = chrono::system_clock::now();
        chrono_time_point nextStepTime = startAt
            + chrono::milliseconds(long(to_double(constDt)*instance->currStep*std::milli::den));

        if (config.throttle && lastStepTime > nextStepTime) {
            Second actualDt(chrono::duration_cast<chrono::milliseconds>(lastStepTime - nextStepTime).count() / std::milli::den);
            int offsetStep = std::ceil(to_double(actualDt / constDt));
            dt = constDt*offsetStep;
            instance->currStep += offsetStep;
        } else {
            dt = constDt;
        }
        std::this_thread::sleep_until(nextStepTime);
    }
}

void Updater::tick(Second dt) {
    instance->tick(dt);
}
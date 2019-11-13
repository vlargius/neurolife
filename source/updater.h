#pragma once
/*
updater system for working with units
*/

#include <memory>
#include <functional>

#include "lib/dimentions.h"

struct IUpdatable {
    long ttl = 0;
    long currStep = 0;
    bool running = true;

    virtual ~IUpdatable() = default;
    virtual void tick(Second dt) = 0;
};

class Updater {
public:
    struct RunConfig {
        Hertz fps     = Hertz{25};
        long  ttl     = 10;
        bool throttle = false;
    };

    Updater(IUpdatable* instance);

    void run(const RunConfig& config);

protected:
    Second constDt = Second(0);
    IUpdatable* instance;

    inline void tick(Second dt);
};
#pragma once
/*
updater system for working with units
*/

#include <memory>
#include <functional>

#include "lib/dimentions.h"

struct IUpdatable
{
    virtual void tick(Second dt) = 0;
};

class Updater {
public:
    struct RunConfig {
        Second dt     = Second{1};
        long ttl      = 10;
        bool throttle = false;
    };

    struct RunStats {

    };

    Updater(IUpdatable* inst);

    void run(const RunConfig& config);
    long getCurrStep() const { return currStep - 1; }

protected:
    long ttl = 0;
    long currStep = 0;
    Second constDt = Second(0);
    IUpdatable* instance;

    inline void tick(Second dt);
};
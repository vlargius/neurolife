#pragma once

#include <iostream>

#include "./../world.h"

class Scale {
   public:
    int operator()(double x) {
        return static_cast<int>((x - source / 2.) / source * target * scale + target / 2. + pos);
    }

    int operator()(const Meter& x) {
        return operator()(to_double(x));
    }

    double scale = 1;
    double pos = 0;

    double target = 10;
    double source = 10;

   protected:
};

class IRender {
   public:
    virtual ~IRender() = default;

    void setInBox(const MeterRect& in_box) {
        xs.source = to_double(in_box.width);
        ys.source = to_double(in_box.height);
    }

    virtual void render(const World& world) = 0;

   protected:
    MeterRect inBox;

    Scale xs;
    Scale ys;
};
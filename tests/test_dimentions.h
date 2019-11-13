#pragma once

#include <ctime>
#include "../source/lib/dimentions.h"
#include "../source/lib/print_dimentions.h"
#include "lib/train.h"

using namespace NTest;

class DimentionTest : public Case {
   public:
    DimentionTest() : Case("Dimentions test") {}

    void run() override {
        srand(time(nullptr));

        double right = (rand() % 1000 - 500) / 3.;
        double left = (rand() % 1000 - 500) / 3.;

        Meter first{left};
        Meter second{right};

        AssertEqual(first, first);
        AssertNotEqual(first, second);

        Assert(first + Meter{1} > first, "compare more");
        Assert(first - Meter{1} < first, "compare less");
        Assert(first + Meter{1} >= first, "more equal");
        Assert(first - Meter{1} <= first, "less equal");
        Assert(first >= first, "more equal");
        Assert(first <= first, "less equal");

        auto val1 = first / Second{left};
        trd::Value<trd::Unit<1, 0, -1>> val2 {to_double(val1)};
        AssertEqual(val1, val2);

        AssertEqual(to_double(first / second), left / right);
        AssertEqual(to_double(first * second), left * right);
        AssertEqual(to_double(first + second), left + right);
        AssertEqual(to_double(first - second), left - right);

        AssertEqual(to_double(first/=second), left/=right);
        AssertEqual(to_double(first*=second), left*=right);
        AssertEqual(to_double(first+=second), left+=right);
        AssertEqual(to_double(first-=second), left-=right);

        AssertEqual(to_double(-first), -left);
        AssertEqual(to_double(+first), +left);

        double k = 314.234;
        AssertEqual(to_double(first * k), left * k);
        AssertEqual(to_double(first / k), left / k);

        AssertEqual(to_double(k * first), k * left);
        AssertEqual(to_double(k / first), k / left);
    }
};

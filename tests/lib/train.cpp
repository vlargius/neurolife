#include "train.h"

namespace NTest {
    Train& Train::get() {
        static Train _instance;
        return _instance;
    }

    Train::~Train() {
        for (Case* test : cases) {
            delete test;
        }
        cases.clear();
    }

    void Train::run() {
        for (Case* test : cases) {
            test->formatRun();
        }
    }

    void Train::addTest(Case* test) {
        cases.push_back(test);
    }
}
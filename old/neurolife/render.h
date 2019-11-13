#pragma once
#include <iostream>

using namespace std;

#include "world.h"

class IRender {
public:
	IRender(const World* w) : w(w) {}
	virtual void run() = 0;
	virtual void flash() = 0;

protected:
	const World* w;
};
#pragma once
#include <iostream>

using namespace std;

#include "world.h"

class Render {
public:
	Render(const World* w) : w(w) {}
	virtual void run() = 0;
	virtual void flash() = 0;

protected:
	const World* w;
};
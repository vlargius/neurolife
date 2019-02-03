#pragma once
#include <iostream>

using namespace std;

#include "world.h";

class Render {
public:
	Render(const World* w) : w(w) {}
	virtual void flash() = 0;
	Render(){}

protected:
	const World* w;
};
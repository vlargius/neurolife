#pragma once


#include "render.h"
#include "world.h"

class Updater {
public:
	Updater(World& w, Render * render);

	void setStepSize(int size);

	void run();

protected:
	World& world;
	Render* render;

	int stepSize;
};

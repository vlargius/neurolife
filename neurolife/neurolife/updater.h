#pragma once


#include "draw_context.h"
#include "world.h"

class Updater {
public:
	Updater(World& w, CharRender& r);

	void setStepSize(int size);

	void run();

protected:
	World& world;
	CharRender& render;

	int stepSize;
};

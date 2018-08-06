#pragma once

#include <stdlib.h>

#include "field.h"

class Actor
{
public:
	Actor(Field * filed);
	~Actor();

	void take_action();

	size_t get_x() const { return x; }
	size_t get_y() const { return y; }

private:
	size_t x;
	size_t y;

	int health;

	Field * field;
};


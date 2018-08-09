#pragma once

#include "field.h"

class Creature
{
public:
	Creature(Field * filed);

	Creature(Field * filed, size_t x, size_t y);

	size_t get_x() const { return x; }
	size_t get_y() const { return y; }

protected:

	size_t x;
	size_t y;

	Field * field;
};


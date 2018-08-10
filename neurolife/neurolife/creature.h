#pragma once

#include "field.h"

class Creature
{
public:
	Creature(Field * filed);

	Creature(Field * filed, size_t x, size_t y);

	void kill() { is_alive = false; }
	bool is_ok() {return is_alive; }

	size_t get_x() const { return x; }
	size_t get_y() const { return y; }

protected:

	size_t x;
	size_t y;

	bool is_alive;

	Field * field;
};


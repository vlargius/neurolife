#pragma once

#include "field.h"

class Creature
{
public:
	Creature(Field * filed);

	Creature(Field * filed, double x, double y);

	void kill() { is_alive = false; }
	bool is_ok() {return is_alive; }

	double get_x() const { return x; }
	double get_y() const { return y; }

protected:

	double x;
	double y;

	bool is_alive;

	Field * field;
};


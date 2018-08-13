#pragma once

#include "field.h"
#include "vec2d.h"

class Creature
{
public:
	Creature(Field * filed);

	Creature(Field * filed, double x, double y);

	void kill() { is_alive = false; }
	virtual bool is_ok() {return is_alive; }

	double x() const { return coor.x; }
	double y() const { return coor.y; }

	const Field* get_field() const { return field; }

protected:

	vec2d coor;

	bool is_alive;

	Field * field;
};


#pragma once

#include "vec2d.h"

class Creature {
public:
	using Id_type = int;
	virtual ~Creature() {};

	const vec2d getPos() const { return position; }
	void setPos(const vec2d& pos) { position = pos; }

	Id_type getId() const { return id; }

protected:
	Creature() {}

	vec2d position;
	Id_type id;
};
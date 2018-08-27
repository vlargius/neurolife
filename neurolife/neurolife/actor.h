#pragma once

#include <stdlib.h>

#include "field.h"
#include "creature.h"
#include "controller.h"
#include "actor_constant.h"

class Grass;

class Actor : public Creature
{
public:
	Actor(Field * filed);

	void live(double dt);
	int get_hp() const { return hp; }

	bool is_ok() override;

	vec2d get_goal() const { return goal; }
	void set_goal(const vec2d& v)  { goal = v; }

	const Controller & get_controller() const { return control; }

private:
	int hp;
	vec2d velocity;
	vec2d goal;

	int decay_speed;

	Controller control;

	void take_action(double dt);	
	void decay();
	void grow();

	void random();
};


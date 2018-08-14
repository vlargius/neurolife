#pragma once

#include <stdlib.h>

#include "field.h"
#include "creature.h"

const double default_decay = 0.5;
const double max_velocity = 70.1;
const double max_acceleration = 1;
const int default_hp = 1000;
const double meal_up = 20;
const double eps = 100;

class Grass;

class Actor : public Creature
{
public:
	Actor(Field * filed);

	void live();
	int get_hp() const { return hp; }

	bool is_ok() override;

	vec2d get_goal() const { return goal; }
	void set_goal(const vec2d& v)  { goal = v; }

private:
	int hp;

	vec2d velocity;

	vec2d goal;

	int decay_speed;
	int curr_decay;

	void take_action();	
	void decay();
	void grow();

	void random();
};


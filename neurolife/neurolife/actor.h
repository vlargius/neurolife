#pragma once

#include <stdlib.h>

#include "field.h"
#include "creature.h"

const double default_decay = 5;
const double default_speed = 10;
const double default_hp = 100;

class Actor : public Creature
{
public:
	Actor(Field * filed);

	void live();
	int get_hp() const { return hp; }

private:
	int hp;

	double move_speed;

	int decay_speed;
	int curr_decay;

	void take_action();	
	void decay();

	void random();
};


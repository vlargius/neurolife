#pragma once

#include <stdlib.h>

#include "field.h"
#include "creature.h"

const int default_decay = 5;
const int default_speed = 2;
const int default_hp = 100;

class Actor : public Creature
{
public:
	Actor(Field * filed);

	void live();
	int get_hp() const { return hp; }

private:
	int hp;

	unsigned move_speed;

	int decay_speed;
	int curr_decay;

	void take_action();	
	void decay();

	void random();
};


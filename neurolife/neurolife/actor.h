#pragma once

#include <stdlib.h>

#include "field.h"
#include "creature.h"

class Actor : public Creature
{
public:
	Actor(Field * filed);

	void take_action();	

private:

	int health;
};


#include "actor.h"


Actor::Actor(Field * field) : 
	filed(field),
	x(2),
	y(5) {
}

Actor::~Actor()
{
}

void Actor::take_action()
{
	int dx = rand() % 10;
	int dy = rand() % 10;


}

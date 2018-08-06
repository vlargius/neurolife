#include "actor.h"
#include "my_utils.h"

Actor::Actor(Field * field) : 
	field(field),
	x(2),
	y(5) {
}

Actor::~Actor()
{
}

void Actor::take_action()
{
	int dx = rand() % 10 - 5;
	int dy = rand() % 10 - 5 ;

	if (field->is_valid(dx + x, dy + y)) {
		x += dx;
		y += dy;
	}

}
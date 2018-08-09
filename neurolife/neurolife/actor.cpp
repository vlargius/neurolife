#include "actor.h"
#include "my_utils.h"

Actor::Actor(Field * field) :
	Creature(field) {

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
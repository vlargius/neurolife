#include "actor.h"

Actor::Actor():
	pos_(),
	move_() {
}

void Actor::tick(double dt, const Field& f) {
	move_.tick(dt, pos_, f);
}

#include "creature.h"

Creature::Creature(Field * f):
	Creature(f, 0, 0) {
}

Creature::Creature(Field * f, double x, double y) :
	field(f),
	coor({ x,y }),
	is_alive(true) {
}

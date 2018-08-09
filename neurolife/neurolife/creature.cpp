#include "creature.h"

Creature::Creature(Field * f):
	Creature(f, 0, 0) {
}

Creature::Creature(Field * f, size_t x, size_t y):
	field(f),
	x(x),
	y(y) {
}

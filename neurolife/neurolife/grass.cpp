#include "grass.h"

Grass::Grass(Field * field): 
	Creature(field, field->get_rand_x(), field->get_rand_y()) {

}

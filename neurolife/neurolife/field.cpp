#include "field.h"


Field::Field() :
	length(0),
	height(0)
{
}

Field::Field(const FieldConf & fcfg) :
	length(fcfg.x),
	height(fcfg.y) {
}



bool Field::is_valid(size_t x, size_t y) const
{
	return x >= 0 && x < length && y >= 0 && y < height;
}

size_t Field::get_rand_x() const
{
	return size_t(rand() % length);
}

size_t Field::get_rand_y() const
{
	return size_t(rand() % height);
}

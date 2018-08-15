#include "field.h"

#include "grass.h"

Field::Field() :
	width(0),
	height(0)
{
}

Field::Field(const FieldConf & fcfg) :
	width(fcfg.x),
	height(fcfg.y) {
}



bool Field::is_valid(const vec2d& vec) const
{
	return vec.x >= 0 && vec.x < width && vec.y >= 0 && vec.y < height;
}

size_t Field::get_rand_x() const
{
	return size_t(rand() % width);
}

size_t Field::get_rand_y() const
{
	return size_t(rand() % height);
}

const list<Grass> Field::get_meal() const
{
	return *meal;
}

#include "field.h"


Field::Field(const FieldConf & fcfg) :
	length(fcfg.x),
	height(fcfg.y) {
}

Field::~Field()
{
}

bool Field::is_valid(size_t x, size_t y) const
{
	return x >= 0 && x < length && y >= 0 && y < height;
}

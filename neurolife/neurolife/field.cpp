#include <string>

#include "field.h"
#include "constants.h"

Field::Field() :
	width(0),
	height(0)
{
}

Field::Field(const FieldConf & fcfg) :
	width(fcfg.x),
	height(fcfg.y) {
}



bool Field::validate(const vec2d& vec) const {
	return vec.x >= 0 && vec.x < width && vec.y >= 0 && vec.y < height;
}

double rndClamp(double to) {
	return static_cast<double>(rand() % static_cast<int>(to));
}

const vec2d Field::getRandomPos() const {
	return { rndClamp(width), rndClamp(height)};
}

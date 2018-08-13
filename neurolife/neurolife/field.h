#pragma once

#include <list>
#include <iostream>

#include "vec2d.h"

using namespace std;

struct FieldConf {
	size_t x;
	size_t y;
};

inline istream& operator>>(istream& is, FieldConf & f_cgf) {
	is >> f_cgf.x >> f_cgf.y;
	return is;
}
class Actor;
class Grass;

class Field
{
public:
	list<Actor> * actors;
	list<Grass> * meal;

	//Grass* get_meal() { return meal-> }

	Field();
	Field(const FieldConf& fcfg);
	bool is_valid(const vec2d& vec) const;

	size_t get_width() const { return width; }
	size_t get_height() const { return height; }

	size_t get_rand_x() const;
	size_t get_rand_y() const;

private:
	size_t width;
	size_t height;	
};
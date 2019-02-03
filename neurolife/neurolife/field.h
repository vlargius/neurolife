#pragma once

#include <list>
#include <iostream>

#include "vec2d.h"

using namespace std;

struct FieldConf {
	double x;
	double y;
};

class Field
{
public:

	Field();
	Field(const FieldConf& fcfg);
	bool validate(const vec2d& vec) const;

	double getWidth() const { return width; }
	double getHeight() const { return height; }

	const vec2d getRandomPos() const;

private:
	double width;
	double height;
};

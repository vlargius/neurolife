#pragma once
#include <math.h>

struct vec2d {
	double x;
	double y;
	
	void normalize() {
		double l = sqrt(x*x + y * y);
		x = x / l;
		y = y / l;
	}

	double len() const {
		return sqrt(x*x + y * y);
	}

	vec2d operator*(double v) const {
		return { x*v, y*v };
	}

	vec2d operator*=(double v) {
		*this = *this*v;
		return *this;
	}

	vec2d operator+(const vec2d& a) const {
		return { x + a.x, y + a.y };
	}

	vec2d operator+=(const vec2d& a) {
		*this = *this + a;
		return *this;
	}

	vec2d operator-(const vec2d& a) const {
		return { x - a.x, y - a.y };
	}

	vec2d operator-() {
		return {-x, -y};
	}

	void trim(double max) {
		if (len() > max) {
			normalize();
			*this *= max;
		}
	}
};
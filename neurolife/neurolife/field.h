#pragma once

#include <vector>
#include <iostream>

using namespace std;

struct FieldConf {
	size_t x;
	size_t y;
};

inline istream& operator>>(istream& is, FieldConf & f_cgf) {
	is >> f_cgf.x >> f_cgf.y;
	return is;
}

class Field
{
public:
	Field();
	Field(const FieldConf& fcfg);
	bool is_valid(size_t x, size_t y) const;

	size_t get_length() const { return length; }
	size_t get_height() const { return height; }

	size_t get_rand_x() const;
	size_t get_rand_y() const;

private:
	size_t length;
	size_t height;
};
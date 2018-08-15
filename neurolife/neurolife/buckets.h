#pragma once

#include <vector>
#include <map>

#include "creature.h"
#include "field.h"

class Actor;

struct bucket_param_t {
	size_t width;
	size_t height;
	double bucket_size;
};

struct Buckets {
	using CreatureInGrid = map<pair<int, int>, vector<const Creature*>>;
	Buckets(const Actor & a, bucket_param_t param);

	const Actor & a;
	bucket_param_t param;

	CreatureInGrid grid;

	void fill();
};

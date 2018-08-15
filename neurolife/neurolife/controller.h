#pragma once

#include <vector>

#include "buckets.h"
#include "network.h"

class Actor;

class Controller {
public:
	enum DirType { x = 0, y = 1 };
	Controller(const Actor* actor, const bucket_param_t& param);

	vec2d get_control();

	const Buckets get_buckets() const { return buckets; }
	const NetworkInput get_input() const { return input; }

protected:
	const Actor & actor;

	Buckets buckets;

	NetworkInput input;
	Network dir[2];


	void set_random_input();

	void calc_input();
};
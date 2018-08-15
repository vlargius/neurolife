#include <random>

#include "controller.h"
#include "constants.h"

Controller::Controller(const Actor * actor, const bucket_param_t& param) :
	actor(*actor),
	input(param.width, param.height),
	dir{ Network(&input), Network(&input) },
	buckets(*actor, param)
{
	for (auto& n : dir) {
		n.get_rand();
	}
}
	
vec2d Controller::get_control() {
	//set_random_input();

	calc_input();

	input.norm();

	return { dir[x].calc(), dir[y].calc() };
}

void Controller::set_random_input() {
	random_device rnd_device;
	mt19937 mersenne_engine{ rnd_device() };
	uniform_real<double> dist{ -1, 1 };

	auto gen = [&dist, &mersenne_engine]() {
		return dist(mersenne_engine);
	};

	for (int i = 0; i < input.width*input.height; ++i) {
		input.at(i) = gen();
	}
}

void Controller::calc_input()
{
	buckets.fill();

	for (int i = 0; i < buckets.param.width; ++i) {
		for (int j = 0; j < buckets.param.height; ++j) {
			input.at(i, j) += buckets.grid[make_pair(i, j)].size() * meal_weight;
		}
	}

}



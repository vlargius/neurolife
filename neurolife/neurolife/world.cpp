#include <algorithm>
#include <memory>
#include <chrono>
#include <map>

#include "world.h"
#include "exceptions.h"
#include "service_symbols.h"
#include "my_utils.h"
#include "constants.h"


World::World() {}

void World::init(const WorldConfig & world_cfg) {
	stepSize = world_cfg.step_size;
	timeToLive = world_cfg.ttl;
	currentStep = 0;
	field = Field(world_cfg.field_cfg);

	for (size_t i = 0; i < world_cfg.actor_count; ++i) {
		Actor a;
		a.getPosComp().setPos(field.getRandomPos());
		actors.emplace_back(a);
	}
}

bool World::alive() {
	return timeToLive > 0;
}

void World::tick(double dt)
{
	++currentStep;

	for (auto& a : actors) {
		a.tick(dt, getField());
	}
}

istream& operator>>(istream& is, WorldConfig & w_cgf) {

	map<string, int> tags;
	string name;
	int value;
	while (is >> name >> value) {
		tags[name] = value;
	}

	w_cgf.field_cfg.x = tags[tags::width];
	w_cgf.field_cfg.y = tags[tags::height];
	w_cgf.actor_count = tags[tags::actors];
	w_cgf.grass_count = tags[tags::grass];
	w_cgf.ttl = tags[tags::ttl];
	w_cgf.step_size = tags[tags::step_size];
	return is;
}
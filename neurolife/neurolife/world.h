#pragma once

#include <iostream>
#include <memory>
#include <sstream>

#include "field.h"
#include "actor.h"

using namespace std;

struct WorldConfig {
	FieldConf	field_cfg;
	unsigned	actor_count;
	size_t		ttl;
};

inline istream& operator>>(istream& is, WorldConfig & w_cgf) {
	is >> w_cgf.field_cfg >> w_cgf.actor_count >> w_cgf.ttl;
	return is;
}


struct OUT_hdl {
	enum Type {Console, GUI};
	OUT_hdl():
		type(Console),
		os(cout) {}

	ostream& os;
	Type type;
};

class World
{
public:
	World();
	~World();

	void init(const WorldConfig& world_cfg);

	void start();
	void stop();

	void step(size_t s = 1);
	void draw();

	OUT_hdl context;

private:
	std::unique_ptr<Field> field;
	vector<Actor> actors;
	size_t time_to_live;
	size_t curr_step;

	bool is_empty(size_t x, size_t y);
};


#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <list>

#include "field.h"
#include "actor.h"
#include "grass.h"

using namespace std;

struct WorldConfig {
	FieldConf	field_cfg;
	unsigned	actor_count;
	unsigned	grass_count;
	size_t		ttl;
};

inline istream& operator>>(istream& is, WorldConfig & w_cgf) {
	is >> w_cgf.field_cfg >> w_cgf.actor_count >> w_cgf.grass_count>> w_cgf.ttl;
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

	void init(const WorldConfig& world_cfg);

	void start();
	void pause();
	void resume();

	void proc();

	void joystick();

	void step(size_t s = 1);
	void draw();

	string get_state() const;

	OUT_hdl context;

private:
	void draw_head(ostream& os);
	void draw_filed(ostream& os);

	std::shared_ptr<Field> field;
	list<Actor> actors;
	list<Grass> meal;

	size_t time_to_live;
	size_t curr_step;

	std::mutex com_lock;

	bool is_active;
	std::condition_variable cond;

	template<class T>
	bool any_of(const list<T> & creatures, size_t x, size_t y) const;
};



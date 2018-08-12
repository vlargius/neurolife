#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <list>
#include <unordered_map>

#include "draw_context.h"
#include "field.h"
#include "actor.h"
#include "grass.h"
#include "view_model.h"

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
class World;


class World
{
public:
	using M2VM=unordered_map<Creature*, BaseViewModel*>; //model to view model
	World();

	void init(const WorldConfig& world_cfg, GUIContext * context);

	void start();
	void stop();
	void start_mt();
	void pause();
	void resume();

	void tick(size_t s = 1);
	void draw();

	string get_state() const;
	size_t get_curr_step() const { return curr_step; }

	const Field * get_field() const { return field.get(); }
	const list<Actor> & get_actors() const { return actors; }
	const list<Grass> & get_meal() const { return meal; }

	const M2VM & get_views() const { return views; }
	
	bool is_meal(size_t x, size_t y) const;
	bool is_actor(size_t x, size_t y) const;

private:
	DrawContext * context;

	std::shared_ptr<Field> field;
	list<Actor> actors;
	list<Grass> meal;

	M2VM views;

	size_t time_to_live;
	size_t curr_step;

	std::mutex com_lock;

	bool is_active;
	std::condition_variable cond;

	void joystick();
	void process();

	template<class T>
	inline bool any_of(const list<T> & l, size_t x, size_t y) const;
};


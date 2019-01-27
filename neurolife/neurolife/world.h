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
#include "gui_context.h"
#include "view_world.h"

using namespace std;

struct WorldConfig {
	FieldConf	field_cfg;
	unsigned	actor_count;
	unsigned	grass_count;
	size_t		ttl;
	size_t		step_size;
};


istream& operator>>(istream& is, WorldConfig & w_cgf);

class World;


class World
{
public:
	World();

	void init(const WorldConfig& world_cfg);

	void start();
	void stop();
	void start_mt();
	void pause();
	void resume();

	void tick(double dt);
	void draw();

	string get_state() const;
	size_t get_curr_step() const { return curr_step; }

	const Field * get_field() const { return field.get(); }
	const list<Actor> & get_actors() const { return actors; }
	const list<Grass> & get_meal() const { return meal; }

	bool is_meal(size_t x, size_t y) const;
	bool is_actor(size_t x, size_t y) const;

	ViewWorld& get_view() { return my_view; }

private:
	ViewWorld my_view;

	std::shared_ptr<Field> field;
	list<Actor> actors;
	list<Grass> meal;

	size_t time_to_live;
	size_t curr_step;
	size_t step_size;

	std::mutex com_lock;

	bool is_active;
	std::condition_variable cond;
	//SDL_Event e;

	void handle_event();
	void process();

	void grow();

	template<class T>
	inline bool any_of(const list<T> & l, size_t x, size_t y) const;
};


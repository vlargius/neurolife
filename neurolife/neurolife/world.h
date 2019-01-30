#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <mutex>
#include <condition_variable>
#include <list>
#include <unordered_map>

#include "field.h"
#include "actor.h"
#include "grass.h"

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
    
	bool isAlive();

	void start();
	void stop();
	void start_mt();

	void tick(double dt);

	size_t getCurrStep() const { return curr_step; }
	bool active() const { return true; }

	const Field * getField() const { return field.get(); }
	const list<Actor> & getActors() const { return actors; }
	const list<Grass> & getMeal() const { return meal; }

	bool is_meal(size_t x, size_t y) const;
	bool is_actor(size_t x, size_t y) const;

private:
	std::shared_ptr<Field> field;
	list<Actor> actors;
	list<Grass> meal;

	size_t time_to_live;
	size_t curr_step;
	size_t step_size;

	std::mutex com_lock;

	std::condition_variable cond;
	//SDL_Event e;

	void handle_event();
	void process();

	void grow();

	template<class T>
	inline bool any_of(const list<T> & l, size_t x, size_t y) const;
};


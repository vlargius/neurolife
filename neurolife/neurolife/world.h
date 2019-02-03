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

using namespace std;

struct WorldConfig {
	FieldConf	field_cfg;
	unsigned	actor_count;
	unsigned	grass_count;
	size_t		ttl;
	size_t		step_size;
};

istream& operator>>(istream& is, WorldConfig & w_cgf);

class World
{
public:
	World();

	void init(const WorldConfig& world_cfg);
    
	bool alive();

	void tick(double dt);

	size_t getCurrStep() const { return currentStep; }
	bool active() const { return true; }

	const Field& getField() const { return field; }

	const list<Actor> & getActors() const { return actors; }

private:
	Field field;
	list<Actor> actors;

	size_t timeToLive;
	size_t currentStep;
	size_t stepSize;

};


#pragma once

#include <memory>

#include "field.h"
#include "actor.h"

struct WorldConfig {
	FieldConf feild_cfg;
	unsigned actor_count;
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

private:
	std::unique_ptr<Field> field;
	vector<Actor> actors;

	bool is_empty(size_t x, size_t y);
};


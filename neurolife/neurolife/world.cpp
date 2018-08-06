#include <algorithm>
#include <iomanip>

#include "world.h"

World::World()
{
}


World::~World()
{
}

void World::init(const WorldConfig & world_cfg)
{
	field = std::make_unique<Field>(world_cfg.feild_cfg);
	for (size_t i = 0; i < world_cfg.actor_count; ++i) {
		actors.emplace_back(field.get());
	}
}

void World::start()
{
	auto& a = actors.front();
	draw();
}

void World::stop()
{
}

void World::step(size_t s)
{
}

void World::draw()
{
	for (size_t i = 0; i < field->get_length(); ++i) {
		for (size_t j = 0; j < field->get_height(); ++j) {
			if (is_empty(i, j)) {
				cout << setw(3) << ".";
			}
			else {
				cout << setw(3) << "A";
			}
		}
		cout << endl;
	}
}

bool World::is_empty(size_t x, size_t y)
{
	return !std::any_of(actors.begin(), actors.end(), [&](const Actor& a) {
		return x == a.get_x() &&  y == a.get_y();
	});
}

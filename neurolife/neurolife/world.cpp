#include <algorithm>
#include <iomanip>
#include <sstream>

#include "world.h"
#include "my_utils.h"
#include "exceptions.h"

World::World()
{
}


World::~World()
{
}

void World::init(const WorldConfig & world_cfg)
{
	time_to_live = world_cfg.ttl;
	curr_step = 0;
	field = std::make_unique<Field>(world_cfg.feild_cfg);
	for (size_t i = 0; i < world_cfg.actor_count; ++i) {
		actors.emplace_back(field.get());
	}
}

void World::start()
{
	for (size_t i = 0; i < time_to_live; ++i) {
		--curr_step;
		my::clear();
		for (auto& a : actors) {
			a.take_action();
		}
		draw();
		my::sleep(1000);
		
		
	}
}

void World::stop()
{
}

void World::step(size_t s)
{
}


void World::draw()
{
	switch (context.type)
	{
	case OUT_hdl::Console:
	{
		ostream& os = context.os;
		for (size_t i = 0; i < field->get_length(); ++i) {
			for (size_t j = 0; j < field->get_height(); ++j) {
				if (is_empty(i, j)) {
					os << setw(3) << ".";
				}
				else {
					os << setw(3) << my::color(my::red) << "A" << my::color(my::white);
				}
			}
			os << endl;
		}
		break;
	}
	default:
		error("not implemented");
		break;
	}
	
}

bool World::is_empty(size_t x, size_t y)
{
	return !std::any_of(actors.begin(), actors.end(), [&](const Actor& a) {
		return x == a.get_x() &&  y == a.get_y();
	});
}

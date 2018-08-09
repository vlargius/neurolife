#include <algorithm>
#include <iomanip>
#include <sstream>
#include <memory>

#include "world.h"
#include "my_utils.h"
#include "exceptions.h"
#include "service_symbols.h"

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
	field = std::make_shared<Field>(world_cfg.field_cfg);
	for (size_t i = 0; i < world_cfg.actor_count; ++i) {
		actors.emplace_back(field.get());
	}

	for (size_t i = 0; i < world_cfg.grass_count; ++i) {
		meal.emplace_back(field.get());
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
				
				if (any_of(meal, i, j)) {
					os << setw(3) << my::color(my::green) << symb_grass << my::color(my::white);
				}
				else if(any_of(actors, i, j)) {
					os << setw(3) << my::color(my::red) << symb_actor << my::color(my::white);
				}
				else {
					os << setw(3) << symb_empty;
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

template<class T>
inline bool World::any_of(const vector<T> & creatures, size_t x, size_t y) const
{
	return std::any_of(creatures.begin(), creatures.end(), [&](const T& c) {
		return x == c.get_x() && y == c.get_y();
	});
}

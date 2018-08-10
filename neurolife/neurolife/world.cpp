#include <algorithm>
#include <iomanip>
#include <sstream>
#include <memory>

#include "world.h"
#include "my_utils.h"
#include "exceptions.h"
#include "service_symbols.h"

World::World():
	is_active(false) {}


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

	field->actors = &actors;
	field->meal = &meal;
}

void World::start()
{	
	is_active = true;
	for (size_t i = 0; i < time_to_live; ++i) {
		while (!is_active) { 
			draw();
			std::unique_lock<std::mutex> lock(com_lock);
            cond.wait(lock);
        }	

		step();

		draw();

		my::sleep(1000);	
		
	}
}

void World::proc() {
	is_active = true;
	
	while(true) {		
		while (!is_active) { 
			std::unique_lock<std::mutex> lock(com_lock);
            cond.wait(lock);
        }
		cout << "i am alive" << endl;
		my::sleep(500);	
	}
}

void World::joystick() {
	while(true) {
		string com;
		cin >> com;
		if(com == quit_key) {
			exit(0);
		}
		if(com == pause_key) {
			pause();
		}
		if(com == resume_key) {
			resume();
		}
	}
}

void World::pause() {
	std::unique_lock<std::mutex> lock(com_lock);
	is_active = false;
	cond.notify_one();
}

void World::resume() {
	std::unique_lock<std::mutex> lock(com_lock);
	is_active = true;
	cond.notify_one();
}

void World::step(size_t s)
{
	++curr_step;
	for(auto& a: actors) {
		a.live();
	}

	actors.remove_if([](Actor & a){ return !a.is_ok();});
	meal.remove_if([](Grass & g){ return !g.is_ok();});
}

string World::get_state() const {
	return (is_active ? "active" : "paused");
}

void World::draw_head(ostream& os) {
	os << "[setp: " << curr_step << "] " 
		<< "[state: " << get_state() << "] " 
		<< "[hp:" << actors.front().get_hp() << "]" 
		<< "[meal: " << meal.size() << "]" <<  endl;
}

void World::draw_filed(ostream& os) {
	for (size_t i = 0; i < field->get_length(); ++i) {
			for (size_t j = 0; j < field->get_height(); ++j) {

				bool is_grass =  any_of(meal, i, j);
				bool is_actor = any_of(actors, i, j);

				if(is_actor && is_grass) {
					os << setw(3) << my::color(my::blue) << symb_consuming << my::color(my::white);
				} else if (is_actor) {
					os << setw(3) << my::color(my::red) << symb_actor << my::color(my::white);
				} else if (is_grass) {
					os << setw(3) << my::color(my::green) << symb_grass << my::color(my::white);
				} else {
					os << setw(3) << symb_empty;
				}
			}
			os << endl;
		}
}

void World::draw()
{
	switch (context.type)
	{
	case OUT_hdl::Console:
	{
		my::clear();
		draw_head(context.os);
		draw_filed(context.os);
		break;
	}
	default:
		error("not implemented");
		break;
	}
	
}

template<class T>
inline bool World::any_of(const list<T> & creatures, size_t x, size_t y) const
{
	return std::any_of(creatures.begin(), creatures.end(), [&](const T& c) {
		return x == c.get_x() && y == c.get_y();
	});
}

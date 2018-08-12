#include <algorithm>
#include <memory>

#include "world.h"
#include "exceptions.h"
#include "service_symbols.h"
#include "my_utils.h"

const int dt = 100;

World::World():
	is_active(false) {}


void World::init(const WorldConfig & world_cfg, DrawContext * context)
{
	this->context = context;
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

void World::start() {
	process();
}

void World::stop()
{
}

void World::start_mt() {
	std::thread main_t(&World::process, this);
	std::thread control_t(&World::joystick, this);

	main_t.join();
	control_t.join();
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

void World::process()
{
	is_active = true;
	for (size_t i = 0; i < time_to_live; ++i) {
		while (!is_active) {
			draw();
			std::unique_lock<std::mutex> lock(com_lock);
			cond.wait(lock);
		}

		tick();
		draw();

		my::sleep(dt);

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

void World::tick(size_t s)
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

bool World::is_meal(size_t x, size_t y) const
{
	return any_of(meal, x, y);
}

bool World::is_actor(size_t x, size_t y) const
{
	return any_of(actors, x, y);
}

template<class T>
inline bool World::any_of(const list<T>& l, size_t x, size_t y) const
{
	return std::any_of(l.begin(), l.end(), [&](const T& c) {
		return x == c.get_x() && y == c.get_y();
	});
}

void World::draw()
{
	context->draw();
}

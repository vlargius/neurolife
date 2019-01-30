#include <algorithm>
#include <memory>
#include <chrono>
#include <map>

#include "world.h"
#include "exceptions.h"
#include "service_symbols.h"
#include "my_utils.h"
#include "constants.h"


World::World() {}


void World::init(const WorldConfig & world_cfg)
{
	step_size = world_cfg.step_size;
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

bool World::isAlive() {
	return time_to_live > 0;
}

void World::start() {
	process();
}

void World::stop()
{
}

void World::start_mt() {
	std::thread main_t(&World::process, this);
	std::thread control_t(&World::handle_event, this);

	main_t.join();
	control_t.join();
}




void World::handle_event() {
	//while (SDL_PollEvent(&e)) {
	//	//If user closes the window
	//	if (e.type == SDL_QUIT) {
	//		is_active = false;
	//	}
	//	//If user presses any key
	//	if (e.type == SDL_KEYDOWN) {
	//		switch (e.key.keysym.sym) {
	//		case SDLK_LEFT:
	//			context->xs.pos += cam_speed;
	//			cout << "l";
	//			break;
	//		case SDLK_RIGHT:
	//			context->xs.pos -= cam_speed;
	//			cout << "r";
	//			break;
	//		case SDLK_UP:
	//			context->ys.pos += cam_speed;
	//			cout << "u";
	//			break;
	//		case SDLK_DOWN:
	//			context->ys.pos -= cam_speed;
	//			cout << "d";
	//			break;
	//		case SDLK_ESCAPE:
	//			is_active = false;
	//		default:
	//			break;
	//		}
	//	}
	//	if (e.type == SDL_MOUSEWHEEL)
	//	{
	//		if (e.wheel.y > 0)
	//		{
	//			context->scale() *= scroll_speed;
	//		}
	//		else if (e.wheel.y < 0)
	//		{
	//			context->scale() /= scroll_speed;
	//		}
	//	}
	//	

	//	
	//}
}

void World::process() {
	/*chrono::steady_clock::time_point from, to;
	
	for (size_t i = 0; i < time_to_live; ++i) {
		while (!is_active) {
			std::unique_lock<std::mutex> lock(com_lock);
			cond.wait(lock);
		}
		double dt = chrono::duration_cast<chrono::milliseconds>(to - from).count();
		from = chrono::steady_clock::now();
		tick(dt);

		handle_event();
		
		my::sleep(step_size);
		to = chrono::steady_clock::now();
	}
	cout << "closing" << endl;*/
}

void World::grow()
{
}

void World::tick(double dt)
{
	++curr_step;
	for(auto& a: actors) {
		a.live(dt);
	}

	/*for (auto& a : actors) {
		if (!a.is_ok()) {
			my_view.remove(a);
		}
	}

	for (auto & m : meal) {
		if (!m.is_ok()) {
			my_view.remove(m);
		}
	}*/
	actors.remove_if([](Actor & a){ return !a.is_ok();});
	meal.remove_if([](Grass & g){ return !g.is_ok();});
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
		return x == c.x() && y == c.y();
	});
}

istream& operator>>(istream& is, WorldConfig & w_cgf) {

	map<string, int> tags;
	string name;
	int value;
	while (is >> name >> value) {
		tags[name] = value;
	}

	w_cgf.field_cfg.x = tags[tags::width];
	w_cgf.field_cfg.y = tags[tags::height];
	w_cgf.actor_count = tags[tags::actors];
	w_cgf.grass_count = tags[tags::grass];
	w_cgf.ttl = tags[tags::ttl];
	w_cgf.step_size = tags[tags::step_size];
	return is;
}
#include <algorithm>
#include <memory>

#include "world.h"
#include "exceptions.h"
#include "service_symbols.h"
#include "my_utils.h"
#include "constants.h"


World::World() :
	is_active(false),
	my_view(*this) {}


void World::init(const WorldConfig & world_cfg, GUIContext * context)
{
	this->context = context;
	time_to_live = world_cfg.ttl;
	curr_step = 0;

	BaseViewModel::c = context;

	field = std::make_shared<Field>(world_cfg.field_cfg);
	for (size_t i = 0; i < world_cfg.actor_count; ++i) {
		actors.emplace_back(field.get());
		auto & a = actors.back();
		my_view.add(a);
	}

	for (size_t i = 0; i < world_cfg.grass_count; ++i) {
		meal.emplace_back(field.get());
		auto & m = meal.back();
		my_view.add(m);
	}

	field->actors = &actors;
	field->meal = &meal;

	context->xs.source = field->get_width();
	context->ys.source = field->get_height();
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
	while (SDL_PollEvent(&e)) {
		//If user closes the window
		if (e.type == SDL_QUIT) {
			is_active = false;
		}
		//If user presses any key
		if (e.type == SDL_KEYDOWN) {
			switch (e.key.keysym.sym) {
			case SDLK_LEFT:
				context->xs.pos += cam_speed;
				cout << "l";
				break;
			case SDLK_RIGHT:
				context->xs.pos -= cam_speed;
				cout << "r";
				break;
			case SDLK_UP:
				context->ys.pos += cam_speed;
				cout << "u";
				break;
			case SDLK_DOWN:
				context->ys.pos -= cam_speed;
				cout << "d";
				break;
			case SDLK_ESCAPE:
				is_active = false;
			default:
				break;
			}
		}
		if (e.type == SDL_MOUSEWHEEL)
		{
			if (e.wheel.y > 0)
			{
				context->scale() *= scroll_speed;
			}
			else if (e.wheel.y < 0)
			{
				context->scale() /= scroll_speed;
			}
		}
		

		
	}
}

void World::process()
{
	is_active = true;
	
	for (size_t i = 0; i < time_to_live && is_active; ++i) {
		while (!is_active) {
			draw();
			std::unique_lock<std::mutex> lock(com_lock);
			cond.wait(lock);
		}

		tick();
		draw();

		handle_event();

		my::sleep(dt);
	}
	cout << "closing" << endl;
}

void World::grow()
{
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

	for (auto& a : actors) {
		if (!a.is_ok()) {
			my_view.remove(a);
		}
	}

	for (auto & m : meal) {
		if (!m.is_ok()) {
			my_view.remove(m);
		}
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
		return x == c.x() && y == c.y();
	});
}

void World::draw() {
	my_view.render();
}

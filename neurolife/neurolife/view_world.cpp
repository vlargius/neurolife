#include <sstream>

#include "view_world.h"
#include "world.h"

void ViewWorld::render() {
		c->clear();
		for (auto v : model2vew) {
			v.second->render();
		}

		draw_statistics();

		c->present();		
}

void ViewWorld::add(const Grass & g) {
	model2vew[&g] = new ViewModel<Grass>(g);
}

void ViewWorld::add(const Actor & a) {
	model2vew[&a] = new ViewModel<Actor>(a);
}

void ViewWorld::remove(const Creature & c) {
	auto it = model2vew.find(&c);
	it->second->~BaseViewModel();	
}


void ViewWorld::draw_statistics() {
	stringstream s1, s2;
	s1 << "[ actors: " << w.get_actors().size() << " ]";
	s2 << "[ meal: " << w.get_meal().size() << " ]";

	const Field * f = w.get_field();

	int x = c->get_width() - c->get_width() / 7;
	int y = c->get_height() / 15;


	c->draw_text({ x, y }, s1.str());
	c->draw_text({ x, y + 30 }, s2.str());
}

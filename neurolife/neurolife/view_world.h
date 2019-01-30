#pragma once

#include <unordered_map>

#include "view_model.h"

class World;

class ViewWorld {
public:

	ViewWorld(World & w) :
		w(w) {}

	void render();

	void add(const Grass& g);
	void add(const Actor& a);

	void remove(const Creature& c);

	const World & get_world() const { return w; }

protected:
	World & w;

	void draw_statistics();
};

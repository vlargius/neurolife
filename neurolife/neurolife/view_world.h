#pragma once

#include <unordered_map>

#include "view_model.h"

class World;

class ViewWorld : public BaseViewModel {
public:
	using M2VM = unordered_map<const Creature*, BaseViewModel*>; //model to view model

	ViewWorld(World & w) :
		w(w) {}

	void render() override;

	void add(const Grass& g);
	void add(const Actor& a);

	void remove(const Creature& c);

	const World & get_world() const { return w; }

protected:
	World & w;
	M2VM model2vew;

	void draw_statistics();
};

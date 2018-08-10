#include <algorithm>
#include <stdlib.h>

#include "actor.h"
#include "my_utils.h"
#include "grass.h"

Actor::Actor(Field * field) :
	Creature(field, field->get_rand_x(), field->get_rand_y()),
	hp(default_hp),
	move_speed(default_speed),
	decay_speed(default_decay),
	curr_decay(decay_speed) {		
}

void Actor::decay() {
	if(curr_decay == 0) {
		--hp;
		curr_decay = decay_speed;
	} else {
		--curr_decay;		
	}
	if(hp == 0) { kill(); }
}

int trim(int i) {
	if(i != 0 && i > 0) {
		i/=i;
	}
	if (i != 0 && i < 0) {
		i /= -i;
	}
	return i;
}

void Actor::take_action() {
	int speed = move_speed;
	int gx = x;
	int gy = y;

	int nx = x;
	int ny = y;

	auto& meal = *field->meal;

	if(meal.size() > 0) {
		auto dist = [&](const Grass& g) { 
			return (g.get_x() - nx)*(g.get_x() - nx) + (g.get_y() - ny) * (g.get_y() - ny);
		};

		auto& g = *std::min_element(meal.begin(), meal.end(), [&](const Grass& l, const Grass& r) {
			return dist(l) < dist(r);
		});
		//set new goal
		gy = g.get_y();
		gx = g.get_x();

		if(x == gx && y == gy) {
			g.kill();
		}
	}

	while(speed != 0) {
		nx+=trim(gx - nx);
		ny+=trim(gy- ny);

		--speed;
	}

	if (field->is_valid(nx, ny)) {
		x = nx;
		y = ny;
	}	
}

void Actor::random() {
	int dx = rand() % 10 - 5;
	int dy = rand() % 10 - 5 ;

	if (field->is_valid(dx + x, dy + y)) {
		x += dx;
		y += dy;
	}	
}

void Actor::live() {
	decay();
	take_action();
}
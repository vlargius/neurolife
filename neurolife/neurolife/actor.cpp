#include <algorithm>
#include <stdlib.h>

#include "actor.h"
#include "my_utils.h"
#include "grass.h"
#include "constants.h"

#undef min;

Actor::Actor(Field * field) :
	Creature(field, field->get_rand_x(), field->get_rand_y()),
	hp(default_hp),
	velocity({ 0,0 }),
	decay_speed(default_decay)
{
}

void Actor::decay() {
	hp -= default_decay;
}

void Actor::grow() {
	hp += meal_up;
	hp = std::min(hp, default_hp);
}

double trim(double i) {
	if(i != 0 && i > 0) {
		i/=i;
	}
	if (i != 0 && i < 0) {
		i /= -i;
	}
	return i;
}

void Actor::take_action() {
	
	vec2d move{ 0,0 };

	auto& meal = *field->meal;
	set_goal({x(), y() });

	if(meal.size() > 0) {
		auto dist = [&](const Grass& g) { 
			return (g.x() - x())*(g.x() - x()) + (g.y() - y()) * (g.y() - y());
		};

		auto& g = *std::min_element(meal.begin(), meal.end(), [&](const Grass& l, const Grass& r) {
			return dist(l) < dist(r);
		});
		
		set_goal({ g.x(), g.y() });
		move = { g.x() - x(), g.y() - y() };

		if(move.len() <= eps) {
			g.kill();
			grow();
		}
	}
	else {
		move = -velocity;
	}

//	move = control.get_control();

	move.normalize();
	move *= max_acceleration;
	velocity += move;

	velocity.trim(max_velocity);
	
	//if(field->is_valid(coor+velocity))
		coor += velocity;
}

void Actor::random() {
	vec2d goal = { rand() % 10 - 5, rand() % 10 - 5 };

	if (field->is_valid(goal)) {
		coor = goal;
	}	
}

void Actor::live() {
	decay();
	take_action();
}

bool Actor::is_ok()
{
	return hp > 0;
}

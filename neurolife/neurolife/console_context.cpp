#include <iostream>
#include <iomanip>

#include "draw_context.h"
#include "my_utils.h"
#include "world.h"
#include "service_symbols.h"

using namespace std;

void ConsoleContext::draw() {
	if (w != nullptr) {
		my::clear();
		draw_head();
		draw_field();
	}
}

void ConsoleContext::draw_head() const {
	os << "[setp: " << w->get_curr_step() << "] "
		<< "[state: " << w->get_state() << "] "
		<< "[hp:" << w->get_actors().front().get_hp() << "]"
		<< "[meal: " << w->get_meal().size() << "]" << endl;
}

void ConsoleContext::draw_field() const {
	const Field * field = w->get_field();
	for (size_t i = 0; i < field->get_width(); ++i) {
		for (size_t j = 0; j < field->get_height(); ++j) {

			bool is_grass = w->is_meal(i, j);
			bool is_actor = w->is_actor(i, j);

			if (is_actor && is_grass) {
				os << setw(3) << my::color(my::blue) << symb_consuming << my::color(my::white);
			}
			else if (is_actor) {
				os << setw(3) << my::color(my::red) << symb_actor << my::color(my::white);
			}
			else if (is_grass) {
				os << setw(3) << my::color(my::green) << symb_grass << my::color(my::white);
			}
			else {
				os << setw(3) << symb_empty;
			}
		}
		os << endl;
	}
}

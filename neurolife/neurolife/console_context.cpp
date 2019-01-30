#include <iostream>
#include <iomanip>

#include "draw_context.h"
#include "my_utils.h"
#include "world.h"
#include "service_symbols.h"

CharRender::CharRender(ostream & os) :
	os(os) {
}

void CharRender::flash(const World& w) {
		utils::clear();
		drawHead(w);
		drawField(w);
}

void CharRender::drawHead(const World& w) const {
	os << "[setp: " << w.getCurrStep() << "] "
		<< "[active: " << (w.active() ? "yes" : "no") << "] "
		<< "[hp:" << w.getActors().front().get_hp() << "]"
		<< "[meal: " << w.getMeal().size() << "]" << endl;
}

void CharRender::drawField(const World& w) const {

	auto& ss = os;

	const Field * field = w.getField();
	for (size_t i = 0; i < field->get_width(); ++i) {
		for (size_t j = 0; j < field->get_height(); ++j) {

			bool is_grass = w.is_meal(i, j);
			bool is_actor = w.is_actor(i, j);

			/*if (is_actor && is_grass) {
				ss << setw(3) << utils::color(utils::blue) << symb_consuming << utils::color(utils::white);
			}
			else*/ 
			if (is_grass) {
				ss << setw(3) << utils::color(utils::green) << symb_grass << utils::color(utils::white);
			}
			else if (is_actor) {
			ss << setw(3) << utils::color(utils::red) << symb_actor << utils::color(utils::white);
			} {
				ss << setw(3) << symb_empty;
			}
		}
		ss << endl;
	}

	//os << ss.str();
}

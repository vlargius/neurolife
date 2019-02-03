#include <iostream>
#include <iomanip>

#include "char_render.h"
#include "my_utils.h"
#include "world.h"
#include "service_symbols.h"

CharRender::CharRender(const World* w, ostream& os) :
	Render(w),
	os(os) {
}

void CharRender::flash() {
		utils::clear();
		drawStat();
		drawField();
}

void CharRender::drawStat() const {
	os  << "[setp: " << w->getCurrStep() << "] "
		<< "[active: " << (w->active() ? "yes" : "no") << "] "
		<< "[actors: " << w->getActors().size() << "]" << endl;
}

void CharRender::drawField() const {
	const Field f = w->getField();
	for (size_t i = 0; i < static_cast<size_t>(f.getWidth()); ++i) {
		for (size_t j = 0; j < static_cast<size_t>(f.getHeight()); ++j) {

			/*if (is_actor && is_grass) {
				ss << setw(3) << utils::color(utils::blue) << symb_consuming << utils::color(utils::white);
			}
			else*/ 
			/*if (is_grass) {
				ss << setw(3) << utils::color(utils::green) << symb_grass << utils::color(utils::white);
			}
			else*/
			//ss << setw(3) << utils::color(utils::red) << symb_actor << utils::color(utils::white);
			//} else {
			os << setw(3) << symb_empty;
		}
		os << endl;
	}
}

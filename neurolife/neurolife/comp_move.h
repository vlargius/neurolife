#pragma once

#include "comp_pos.h"
#include "field.h"

namespace comp {
	class Move {
	public:

		void tick(double dt, comp::Position& pos, const Field& f) {	
			pos.setPos(f.getRandomPos());
		}

	protected:
	};
}

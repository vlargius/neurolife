#pragma once

#include "vec2d.h"

namespace comp {

class Position{
	public:
		
		const vec2d getPos() const { return position; }
		void setPos(const vec2d& pos) { position = pos; }

	protected:
		vec2d position;
	};
}
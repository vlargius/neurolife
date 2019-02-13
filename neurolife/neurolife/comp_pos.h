#pragma once

#include <string>
#include <sstream>

using namespace std;

#include "vec2d.h"

namespace comp {

class Position{
	public:
		
		const vec2d getPos() const { return position; }
		void setPos(const vec2d& pos) { position = pos; }

		string serialize() const { return to_string(position.x) +
			" " +
			to_string(position.y);
		}

		void deserialize(const string& s) {
			stringstream ss(s);
			ss >> position.x >> position.y;
		}

	protected:
		vec2d position;
	};
}
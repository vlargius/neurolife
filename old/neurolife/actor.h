#pragma once

#include "comp_pos.h"
#include "comp_move.h"
#include "field.h"

class Actor {
public:
	Actor();

	void tick(double dt, const Field& f);

	comp::Move& getMoveComp() { return move_; }
	comp::Position & getPosComp() { return pos_; }

	const comp::Position & getPosComp() const { return pos_; }

protected:
	comp::Position pos_;
	comp::Move move_;
};
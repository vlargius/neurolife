#include "actor.h"

#include "lib/print_dimentions.h"

std::ostream& operator<<(std::ostream& os, const Position& p) {
    return os << "(" << p.x << ", " << p.y << ")";
}

std::ostream& operator<<(std::ostream& os, const Actor& a) {
    return os << "actor: " << a.pos;
}
#include "actor.h"

#include "lib/print_dimentions.h"

std::ostream& operator<<(std::ostream& os, const Actor& a) {
    return os << "actor: " << a.pos;
}

Meter Actor::distance(const Actor& other) {
    return norm(pos - other.pos);
}
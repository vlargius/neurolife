#include "world.h"


std::ostream& operator<<(std::ostream& os, const World& world) {
    os << "world: " << std::endl;
    for (const Actor& actor : world.actors) {
        os << actor << std::endl;
    }
    return os;
}
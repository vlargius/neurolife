#include "manager.h"
#include <iomanip>
#include <iostream>

#include "input_manager.h"

static const char* red{"\033[0;31m"};
static const char* green{"\x1B[32m"};
static const char* reset{"\x1B[0m"};

Manager::Manager(
    const World::CreateConf& w_conf,
    const Second& phys_dt,
    const CharRender::CreateConf& r_conf) : physDt(phys_dt),
                                            world(w_conf),
                                            render(new CharRender(r_conf)) {}

Manager::Manager(
    const World::CreateConf& w_conf,
    const Second& phys_dt,
    const GuiRender::CreateConf& r_conf) : physDt(phys_dt),
                                           world(w_conf),
                                           render(new GuiRender(r_conf)) {}

Manager::~Manager() {
    delete render;
    render = nullptr;
}

void Manager::tick(Second) {
    tickInput();
    tickPhys(physDt);
    system("clear");
    const char* sep = "  ";
    std::cout << "[ttl: " << ttl << "]" << sep
              << "[step: " << green << std::setw(3) << currStep << reset << "]" << std::endl;
    render->render(world);
}

void Manager::tickPhys(Second dt) {
    for (Actor& actor : world.actors) {
        if (!world.isIn(actor)) {
            auto normalVel = world.getNormalCollision(actor);
            actor.vel -= 2 * (dot(normalVel, actor.vel)) * normalVel;
            actor.force = Force{};
        }

        // if (false)
        //Newton's 2'nd law
        {
            // double G = 1;//6.673e-11;
            Meter eps = Meter(1.e-20);
            for (Actor& actorB : world.actors) {
                const Meter minDist{0.1};
                Position deltaPos = actorB.pos - actor.pos;
                Meter distance = norm(deltaPos);
                if (distance > minDist) {
                    double eps = 1.e-10;
                    distance.value += eps;
                    Newton F = (actor.mass * actorB.mass * G) / (distance * distance);
                    actor.force += F * deltaPos / distance;
                }
            }
        }

        actor.vel += actor.force / actor.mass * dt;
        actor.pos += actor.vel * dt;
    }
}

void Manager::tickInput() {
    InputState inputState;
    do_input(inputState);

    if (inputState.quit)
        running = false;
}
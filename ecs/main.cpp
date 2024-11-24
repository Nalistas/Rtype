#include "registry.hpp"
#include <iostream>
#include <string>

struct position {
    int x;
    int y;

    position(int x, int y) : x(x), y(y) {}
};

struct velocity {
    int vx;
    int vy;

    velocity(int vx, int vy) : vx(vx), vy(vy) {}
};

void logging_system(ecs::registry &r)
{
    auto const &positions = r.get_components<position>();
    auto const &velocities = r.get_components<velocity>();

    std::cerr << "Found " << positions.size() << " positions and " << velocities.size() << " velocities." << std::endl;
    for (size_t i = 0; i < positions.size(); ++i) {
        auto const &pos = positions[i];
        if (!pos.has_value()) {
            continue;
        }
        std::cerr << "Position: " << pos->x << ", " << pos->y << std::endl;
    }

    for (size_t i = 0; i < velocities.size(); ++i) {
        auto const &vel = velocities[i];
        if (!vel.has_value()) {
            continue;
        }
        std::cerr << "Velocity: " << vel->vx << ", " << vel->vy << std::endl;
    }
}

int main() {
    ecs::registry reg;
    ecs::entity e = reg.create_entity();

    reg.register_component<position>();
    reg.register_component<velocity>();

    reg.emplace_component<velocity>(e, 3, 4);
    // reg.emplace_component<position>(e, 1, 2);
    reg.emplace_component<position>(e, 5, 6);

    ecs::entity e2 = reg.create_entity();

    reg.emplace_component<position>(e2, 7, 8);

    logging_system(reg);

    reg.delete_entity(e);

    return 0;
}

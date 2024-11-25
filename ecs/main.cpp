#include "registry.hpp"
#include "isystem.hpp"
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

class logging_system : public ecs::isystem<position, velocity> {
    public:
    void operator()( sparse_array<position>& positions, sparse_array<velocity>& velocities) const override
    {
        std::cout << "Positions:" << std::endl;
        for (auto const &pos : positions) {
            if (pos.has_value()) {
                std::cout << pos->x << " " << pos->y << std::endl;
            }
        }
        std::cout << "Velocities:" << std::endl;
        for (auto const &vel : velocities) {
            if (vel.has_value()) {
                std::cout << vel->vx << " " << vel->vy << std::endl;
            }
        }
    }
};

int main() {
    ecs::registry reg;
    ecs::entity e = reg.create_entity();

    reg.register_component<position>();
    reg.register_component<velocity>();

    reg.emplace_component<velocity>(e, 3, 4);
    reg.emplace_component<position>(e, 5, 6);

    ecs::entity e2 = reg.create_entity();

    reg.emplace_component<position>(e2, 7, 8);

    reg.add_system<position, velocity>(logging_system());

    reg.run_systems();
    reg.delete_entity(e);

    return 0;
}

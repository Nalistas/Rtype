/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include "ecs.hpp"
#include "registry.hpp"
#include "isystem.hpp"
#include <iostream>

class Position {
    public:
        float x;
        float y;
        Position(float x, float y) : x(x), y(y) {}
};

class Velocity {
    public:
        float x;
        float y;
        Velocity(float x, float y) : x(x), y(y) {}
};

class MySystem : public ecs::isystem<Position, Velocity> {
    public:
        void operator()(ecs::iregistry &r, Position &p, Velocity &v) const override {
            (void)r;
            std::cout << p.x << " " << p.y << " " << v.x << " " << v.y << std::endl;
        }
};

void run_systems(ecs::registry &r)
{
    r.run_systems();
}

int main()
{
    ecs::registry reg;

    reg.register_component<Position>();
    reg.register_component<Velocity>();

    ecs::entity e = reg.create_entity();
    ecs::entity e2 = reg.create_entity();
    ecs::entity e3 = reg.create_entity();

    reg.emplace_component<Position>(e, 1, 2);

    reg.emplace_component<Velocity>(e2, 3, 4);

    reg.emplace_component<Position>(e3, 5, 6);
    reg.emplace_component<Velocity>(e3, 7, 8);

    reg.add_system<Position, Velocity>(MySystem());

    run_systems(reg);

    reg.emplace_component<Position>(e2, 9, 10);

    run_systems(reg);

    return 0; 
}

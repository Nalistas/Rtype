/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <iostream>
#include "ecs/include/registry.hpp"
#include "ecs/include/entity.hpp"
#include "ecs/include/isystem.hpp"

class Position {
    public:
        Position(float x, float y) : x(x), y(y) {}
        float x;
        float y;
};

class MySystem : public ecs::isystem<Position> {
    public:
        void operator()(ecs::iregistry &r, sparse_array<Position>& sa2) const override
        {
            for (auto &component : sa2) {
                if (!component.has_value())
                    continue;
                std::cout << component.value().x << " " << component.value().y << std::endl;
            }
        }
};
        // do something

int main(void)
{
    ecs::registry r;

    r.register_component<Position>();
    r.add_system<Position>(MySystem());

    ecs::entity e = r.create_entity();
    r.emplace_component<Position>(e, 1, 2);

    r.run_systems();

    return 0;
}

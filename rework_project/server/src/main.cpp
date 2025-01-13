/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** main
*/

#include <iostream>
#include "RoomsCore.hpp"
#include "registry.hpp"
#include "isystem.hpp"

struct speed {
    int x;
    int y;
};

struct position {
    int x;
    int y;
};

class MovementSystem : public ecs::isystem<speed, position> {
    public:
        MovementSystem() = default;
        ~MovementSystem() = default;

        void operator()(ecs::registry &registry, sparse_array<speed> &speeds, sparse_array<position> &positions) override {
            (void)registry;
            for (auto [index, speed, position] : zipper(speeds, positions)) {
                std::cout << "coucou " << index << std::endl;
            }
        }
};

class NoneSystem : public ecs::isystem<> {
    public:
        NoneSystem() = default;
        ~NoneSystem() = default;
    
        void operator()(ecs::registry &registry) override
        {
            (void)registry;
            std::cout << "NoneSystem" << std::endl;
        }
};


int main()
{
     RoomsCore core("12345");
     core.run();
/*
    ecs::registry registry;

    registry.register_component<position>();
    registry.register_component<speed>();
    registry.add_system<speed, position>(MovementSystem());

    auto e = registry.create_entity();
    auto e2 = registry.create_entity();
    auto e3 = registry.create_entity();

    std::cout << "e = " << e << ", e2 = " << e2 << ", e3 = " << e3 <<  std::endl;

    registry.emplace_component<position>(e);
    registry.emplace_component<speed>(e);

    registry.get_components<position>()[e] = { 1, 2 };
    registry.get_components<speed>()[e] = { 3, 4 };

    registry.emplace_component<position>(e2);
    registry.get_components<position>()[e2] = { 5, 6 };

    registry.emplace_component<speed>(e3);
    registry.get_components<speed>()[e3] = { 7, 8 };

    std::cout << registry.get_components<position>()[e].has_value() << std::endl;
    std::cout << registry.get_components<speed>()[e].has_value() << std::endl;

    registry.add_system<>(NoneSystem());

    registry.run_systems();
    return 0;
    */
}

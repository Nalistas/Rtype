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
#include "GameLauncher.hpp"

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
    // GameLauncher launcher("./libr-type.so");
    // std::list<GameLauncher::Player> players = {{"player1", "127.0.0.1"}, {"player2", "127.0.0.1"}, {"player3", "127.0.0.1"}};
    // launcher.launch(players);

    RoomsCore core("12345");
    core.run();
/*
    ecs::registry registry;

    // RoomsCore core("12345");
    // core.run();
    return 0;
    */
}

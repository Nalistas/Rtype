/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameCore
*/

#include "GameCore.hpp"

GameCore::GameCore(
                std::shared_ptr<ecs::registry> &reg,
                ServerActionsGetter const &get_actions,
                std::function<void()> updateScreen
            ) :
    _registry(reg), _get_actions(get_actions), _updateScreen(updateScreen)
{
}

GameCore::~GameCore()
{
}

void GameCore::run(void)
{
    while (true) {
        // std::cout << "running game" << std::endl;
        auto actions = _get_actions();

        // std::cout << "actions size: " << actions.size() << std::endl;

        for (auto &action : actions) {
            action();
        }

        // std::cout << "running systems" << std::endl;
        _registry->run_systems();
        _updateScreen();
        // std::cout << "running systems done" << std::endl;
    }
}

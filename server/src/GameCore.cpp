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
                std::function<void(std::size_t)> updateScreen
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
        auto actions = _get_actions();
        for (auto &action : actions) {
            action();
        }
        _registry->run_systems();
    }
}

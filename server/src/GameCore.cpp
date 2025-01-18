/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameCore
*/

#include "GameCore.hpp"

GameCore::GameCore(
                std::shared_ptr<ecs::registry> &reg,
                ServerActionsGetter const &get_actions
            ) :
    _registry(reg), _get_actions(get_actions)
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

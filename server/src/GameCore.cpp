/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameCore
*/

#include "GameCore.hpp"
#include <chrono>

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
    auto time_last_update = std::chrono::system_clock::now();

    while (true) {
        auto actions = _get_actions();
        for (auto &action : actions) {
            action();
            time_last_update = std::chrono::system_clock::now();
        }
        _registry->run_systems();
        auto now = std::chrono::system_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - time_last_update).count();
        if (elapsed_time > 10000) {
            std::cout << "GameCore: " << elapsed_time << " stopping" << std::endl;
            return;
        }
    }
}

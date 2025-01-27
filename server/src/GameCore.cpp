/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameCore
*/

#include "GameCore.hpp"
#include <chrono>
#include <thread>

GameCore::GameCore(
                std::shared_ptr<ecs::registry> &reg,
                ServerActionsGetter const &get_actions,
                std::function<void(std::size_t)> updateScreen
            ) :
    _registry(reg), _get_actions(get_actions), _updateScreen(updateScreen), isRunning(true)
{
}

GameCore::~GameCore()
{
}

void GameCore::getActionsClient(void)
{
    while (isRunning) {
        auto actions_log = _get_actions();
        if (!actions_log.empty()) {
            std::lock_guard<std::mutex> guard(_actions_mutex);
            _actions.splice(_actions.end(), actions_log);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void GameCore::executeActions(void)
{

    auto now = std::chrono::system_clock::now();

    if (_actions.empty()) {
        auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - _time_last_update).count();
        if (elapsed_time < 10000) {
            return;
        }
        isRunning = false;
        return;
    }
    _time_last_update = now;
    {
        std::lock_guard<std::mutex> guard(_actions_mutex);
        for (auto &action : _actions) {
            action();
        }
        _actions.clear();
    }
}

void GameCore::run(void)
{
    std::thread get_actions(&GameCore::getActionsClient, this);
    _time_last_update = std::chrono::system_clock::now();

    while (isRunning) {
        executeActions();
        _registry->run_systems();
    }
    get_actions.join();
}

// void GameCore::run(void)
// {
//     auto time_last_update = std::chrono::system_clock::now();
//     isRunning = true;

//     while (isRunning) {
//         auto actions = _get_actions();
//         if (actions.empty()) {
//             auto now = std::chrono::system_clock::now();
//             auto elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - time_last_update).count();
//             _registry->run_systems();
//             if (elapsed_time > 10000) {
//                 std::cout << "GameCore: " << elapsed_time << " stopping" << std::endl;
//                 return;
//             }
//             continue;
//         }
//         time_last_update = std::chrono::system_clock::now();
//         std::list<std::thread> threads;
//         for (auto &action : actions) {
//             threads.emplace_back(std::thread(action));
//         }
//         for (auto &thread : threads) {
//             thread.join();
//         }
//         _registry->run_systems();
//     }
// }

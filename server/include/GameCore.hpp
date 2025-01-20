/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameCore
*/

#include "registry.hpp"
#include "IGame.hpp"
#include <functional>
#include <memory>
#include <mutex>

#ifndef GAMECORE_HPP_
    #define GAMECORE_HPP_

class GameCore {

    public:
        using ServerActions = std::list<std::function<void()>>;
        using ServerActionsGetter = std::function<ServerActions()>;

        /**
         * @brief Construct a new Game Core object
         * @param reg the registry of the game, initialized by the game launcher, see GameLauncher::launch
         * @param get_actions a function to get the server actions, which is a function that returns
         *                    a list of functions to be executed
         */
        GameCore(std::shared_ptr<ecs::registry> &reg, ServerActionsGetter const &get_actions, std::function<void(std::size_t)> updateScreen);

        /**
         * @brief Destroy the Game Core object
         */
        ~GameCore();

        /**
         * @brief Run the game core
         */
        void run(void);

    private:
        std::mutex _registry_mutex;

        std::shared_ptr<ecs::registry> _registry;
        ServerActionsGetter const &_get_actions;
        std::function<void(std::size_t)> _updateScreen;
        bool isRunning = true;
        std::chrono::_V2::system_clock::time_point _time_last_update;
};

#endif /* !GAMECORE_HPP_ */

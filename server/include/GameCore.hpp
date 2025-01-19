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
        std::shared_ptr<ecs::registry> _registry;
        ServerActionsGetter const &_get_actions;
        std::function<void(std::size_t)> _updateScreen;
};

#endif /* !GAMECORE_HPP_ */

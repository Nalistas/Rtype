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
        
        GameCore(ecs::registry &reg, ServerActionsGetter const &get_actions);
        ~GameCore();

        void run(void);

    private:
        ecs::registry &_registry;
        ServerActionsGetter const &_get_actions;
};

#endif /* !GAMECORE_HPP_ */

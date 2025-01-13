/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameCore
*/

#include "registry.hpp"
#include "IGame.hpp"
#include <memory>

#ifndef GAMECORE_HPP_
    #define GAMECORE_HPP_

class GameCore {
    public:
        GameCore(std::shared_ptr<rtype::IGame> &game);
        ~GameCore();

    private:
        ecs::registry _registry;
};

#endif /* !GAMECORE_HPP_ */

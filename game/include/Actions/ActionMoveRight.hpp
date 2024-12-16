/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveRight
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef ACTIONMOVERIGHT_HPP_
#define ACTIONMOVERIGHT_HPP_

class ActionMoveRight: public rtype::IClientActionHandler {
    public:
        ActionMoveRight(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate);
        ~ActionMoveRight();
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    protected:
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::function<void(ecs::entity const &)> _broadcastUpdate;
};

#endif /* !ACTIONMOVERIGHT_HPP_ */
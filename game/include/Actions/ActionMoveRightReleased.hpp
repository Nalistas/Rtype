/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveUp
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef ACTIONMOVERIGHTRELEASED_HPP_
#define ACTIONMOVERIGHTRELEASED_HPP_

class ActionMoveRightReleased: public rtype::IClientActionHandler {
    public:
        ActionMoveRightReleased(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate);
        ~ActionMoveRightReleased();
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    protected:
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::function<void(ecs::entity const &)> _broadcastUpdate;
};

#endif /* !ACTIONMOVERIGHTRELEASED_HPP_ */
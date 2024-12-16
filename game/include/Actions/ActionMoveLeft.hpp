/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveUp
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef ACTIONMOVELEFT_HPP_
#define ACTIONMOVELEFT_HPP_

class ActionMoveLeft: public rtype::IClientActionHandler {
    public:
        ActionMoveLeft(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate);
        ~ActionMoveLeft();
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    protected:
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::function<void(ecs::entity const &)> _broadcastUpdate;
};

#endif /* !ACTIONMOVELEFT_HPP_ */

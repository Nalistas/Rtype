/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveUp
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef ACTIONCREATEBULLET_HPP_
#define ACTIONCREATEBULLET_HPP_

class ActionCreateBullet: public rtype::IClientActionHandler {
    public:
        ActionCreateBullet(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastCreate);
        ~ActionCreateBullet();
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    protected:
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::function<void(ecs::entity const &)> _broadcastCreate;
};

#endif /* !ACTIONCREATEBULLET_HPP_ */

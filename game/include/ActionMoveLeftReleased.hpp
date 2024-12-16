/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveUp
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef ACTIONMOVELEFTRELEASED_HPP_
#define ACTIONMOVELEFTRELEASED_HPP_

class ActionMoveLeftReleased: public rtype::IClientActionHandler {
    public:
        ActionMoveLeftReleased(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate);
        ~ActionMoveLeftReleased();
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    protected:
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::function<void(ecs::entity const &)> _broadcastUpdate;
};

#endif /* !ACTIONMOVELEFTRELEASED_HPP_ */

/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveUp
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef ACTIONMOVEDOWNRELEASED_HPP_
#define ACTIONMOVEDOWNRELEASED_HPP_

class ActionMoveDownReleased: public rtype::IClientActionHandler {
    public:
        ActionMoveDownReleased(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate);
        ~ActionMoveDownReleased();
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    protected:
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::function<void(ecs::entity const &)> _broadcastUpdate;
};

#endif /* !ACTIONMOVEDOWNRELEASED_HPP_ */

/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemDeleteEnemy
*/

#include "isystem.hpp"
#include "registry.hpp"
#include "GraphicsPrimitives.hpp"

#include <functional>

#ifndef SYSTEMDELETEENEMY_HPP_
#define SYSTEMDELETEENEMY_HPP_

class SystemDeleteEnemy: public ecs::isystem<graphics_interface::Sprite>  {
    public:
        SystemDeleteEnemy(std::function<void(ecs::entity const &)> broadcastDelete);
        ~SystemDeleteEnemy();

        void operator()(ecs::registry &registry, ecs::entity const &e, graphics_interface::Sprite &sprite);

    protected:
    private:
        std::function<void(ecs::entity const &)> _broadcastDelete;
};

#endif /* !SYSTEMDELETEENEMY_HPP_ */

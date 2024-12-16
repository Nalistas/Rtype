/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemManageBullets
*/

#include "isystem.hpp"
#include "registry.hpp"
#include "GraphicsPrimitives.hpp"
#include "Health.hpp"
#include "Camp.hpp"
#include "Damage.hpp"

#include <functional>

#ifndef SYSTEMMANAGEBULLETS_HPP_
#define SYSTEMMANAGEBULLETS_HPP_

class SystemManageBullets: public ecs::isystem<graphics_interface::Sprite, Camp, Damage> {
    public:
        SystemManageBullets(std::function<void(ecs::entity const &)> broadcastDelete);
        ~SystemManageBullets();
        void operator()(ecs::registry &r , ecs::entity const &e, graphics_interface::Sprite &sprite, Camp &camp, Damage &damage);

    protected:
    private:
        std::function<void(ecs::entity const &)> _broadcastDelete;

};

#endif /* !SYSTEMMANAGEBULLETS_HPP_ */

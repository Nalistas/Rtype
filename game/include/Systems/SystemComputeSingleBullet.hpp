/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemComputeSingleBullet
*/

#include "isystem.hpp"
#include "registry.hpp"
#include "GraphicsPrimitives.hpp"
#include "Health.hpp"
#include "Camp.hpp"
#include "Damage.hpp"

#include <functional>

#ifndef SYSTEMCOMPUTESINGLEBULLET_HPP_
#define SYSTEMCOMPUTESINGLEBULLET_HPP_

class SystemComputeSingleBullet: public ecs::isystem<Health, graphics_interface::Sprite, Camp>  {
    public:
        SystemComputeSingleBullet(Camp &bullet_camp, Damage damage, graphics_interface::Sprite &bullet_sprite, std::function<void(ecs::entity const &)> broadcastDelete);
        ~SystemComputeSingleBullet();
        void operator()(ecs::registry &r, ecs::entity const &e, Health &health, graphics_interface::Sprite &sprite, Camp &camp) override;

    protected:
    private:
        Camp _bullet_camp;
        Damage _damage;
        graphics_interface::Sprite _sprite;
        std::function<void(ecs::entity const &)> _broadcastDelete;
};

#endif /* !SYSTEMCOMPUTESINGLEBULLET_HPP_ */

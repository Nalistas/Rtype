/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemComputeSingleBullet
*/

#include "Systems/SystemComputeSingleBullet.hpp"
#include  <iostream>

SystemComputeSingleBullet::SystemComputeSingleBullet(bool &has_hit, Camp &bullet_camp, Damage damage, graphics_interface::Sprite &bullet_sprite, std::function<void(ecs::entity const &)> broadcastDelete)
    : has_hit(has_hit), _bullet_camp(bullet_camp), _damage(damage), _sprite(bullet_sprite), _broadcastDelete(broadcastDelete)
{
}

SystemComputeSingleBullet::~SystemComputeSingleBullet()
{
}

void SystemComputeSingleBullet::operator()(ecs::registry &r, ecs::entity const &e, Health &health, graphics_interface::Sprite &sprite_2, Camp &camp)
{
    if (_bullet_camp.getCamp() == camp.getCamp() || has_hit) {
        return;
    }

    std::cout << "bullet hit enemy" << std::endl;
    std::cout << sprite_2.pos_x << " - " << sprite_2.pos_x + sprite_2.size_x  << std::endl;
    std::cout << sprite_2.pos_y << " - " << sprite_2.pos_y + sprite_2.size_y << std::endl;
    std::cout << _sprite.pos_x << " - " << _sprite.pos_x + _sprite.size_x << std::endl;
    std::cout << _sprite.pos_y << " - " << _sprite.pos_y + _sprite.size_y << std::endl;


    bool check1 = _sprite.pos_x <= sprite_2.pos_x && sprite_2.pos_x <= _sprite.pos_x + _sprite.size_x;
    check1 = check1 | (_sprite.pos_x <= sprite_2.pos_x + sprite_2.size_x && sprite_2.pos_x + sprite_2.size_x <= _sprite.pos_x + _sprite.size_x);
    bool check2 = _sprite.pos_y <= sprite_2.pos_y && sprite_2.pos_y <= _sprite.pos_y + _sprite.size_y;
    check2 = check2 | (_sprite.pos_y <= sprite_2.pos_y + sprite_2.size_y && sprite_2.pos_y + sprite_2.size_y <= _sprite.pos_y + _sprite.size_y);
    if (!check1 || !check2) {
        return;
    }

    health.setHealth(health.getHealth() - _damage.getDamage());
    std::cout << "bullet hit enemy" << std::endl;
    if (health.getHealth() <= 0) {
        _broadcastDelete(e);
        r.delete_entity(e);
        return;
    }
}

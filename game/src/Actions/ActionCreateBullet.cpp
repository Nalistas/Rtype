/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveDown
*/

#include "Actions/ActionCreateBullet.hpp"
#include "Camp.hpp"
#include "Damage.hpp"
#include "GraphicsPrimitives.hpp"

ActionCreateBullet::ActionCreateBullet(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastCreate)
    : _registry(registry), _broadcastCreate(broadcastCreate)
{
}

ActionCreateBullet::~ActionCreateBullet()
{
}

void ActionCreateBullet::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    ecs::entity bullet = _registry->create_entity();
    graphics_interface::Sprite sprite;
    if (_registry->get_components<graphics_interface::Sprite>()[client].has_value()) {
        sprite.pos_x = _registry->get_components<graphics_interface::Sprite>()[client].value().pos_x + 35;
        sprite.pos_y = _registry->get_components<graphics_interface::Sprite>()[client].value().pos_y;
    } else {
        sprite.pos_x = 100;
        sprite.pos_y = 100; 
    }
    sprite.speed_x = 1;
    sprite.speed_y = 0;;
    sprite.path = "./bullet.png";
    sprite.nb_frames = 1;
    sprite.ms_per_frame = 0;
    sprite.size_x = 27;
    sprite.size_y = 30;
    sprite.text_rect_width = 0;
    sprite.text_rect_height = 0;
    sprite.offset_x = 0;
    sprite.offset_y = 0;
    _registry->emplace_component<graphics_interface::Sprite>(bullet, sprite);
    _registry->emplace_component<Camp>(bullet, 0);
    _registry->emplace_component<Damage>(bullet, 5);

    _broadcastCreate(bullet);
    std::cout << "create bullet" << std::endl;
}

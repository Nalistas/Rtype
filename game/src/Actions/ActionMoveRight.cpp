/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveRight
*/

#include "Actions/ActionMoveRight.hpp"
#include "GraphicsPrimitives.hpp"

ActionMoveRight::ActionMoveRight(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate)
    : _registry(registry), _broadcastUpdate(broadcastUpdate)
{
}

ActionMoveRight::~ActionMoveRight()
{
}

void ActionMoveRight::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (_registry->get_components<graphics_interface::Sprite>()[client].has_value()) {
        _registry->get_components<graphics_interface::Sprite>()[client].value().speed_x = 2;
        _broadcastUpdate(ecs::entity(client));
        std::cout << static_cast<int>(_registry->get_components<graphics_interface::Sprite>()[client].value().speed_x) << std::endl;
    }
}

/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveUp
*/

#include "ActionMoveUp.hpp"
#include "GraphicsPrimitives.hpp"

ActionMoveUp::ActionMoveUp(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate)
    : _registry(registry), _broadcastUpdate(broadcastUpdate)
{
}

ActionMoveUp::~ActionMoveUp()
{
}

void ActionMoveUp::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    if (_registry->get_components<graphics_interface::Sprite>()[client].has_value()) {
        _registry->get_components<graphics_interface::Sprite>()[client].value().speed_y = -2;
        _broadcastUpdate(ecs::entity(client));
        std::cout << static_cast<int>(_registry->get_components<graphics_interface::Sprite>()[client].value().speed_x) << std::endl;
    }
}

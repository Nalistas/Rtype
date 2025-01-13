/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** ActionMoveDown
*/

#include "Actions/ActionMoveDown.hpp"
#include "GraphicsPrimitives.hpp"

ActionMoveDown::ActionMoveDown(std::shared_ptr<ecs::registry> registry, std::function<void(ecs::entity const &)> broadcastUpdate)
    : _registry(registry), _broadcastUpdate(broadcastUpdate)
{
}

ActionMoveDown::~ActionMoveDown()
{
}

void ActionMoveDown::operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y)
{
    (void) mouse_x;
    (void) mouse_y;
    if (_registry->get_components<graphics_interface::Sprite>()[client].has_value()) {
        _registry->get_components<graphics_interface::Sprite>()[client].value().speed_y = 2;
        _broadcastUpdate(ecs::entity(client));
        std::cout << static_cast<int>(_registry->get_components<graphics_interface::Sprite>()[client].value().speed_x) << std::endl;
    }
}

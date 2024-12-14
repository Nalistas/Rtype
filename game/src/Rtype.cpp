/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "RtypePlayer.hpp"
#include "registry.hpp"
#include "Rtype.hpp"

Rtype::Rtype()
{}

Rtype::~Rtype()
{}

std::string Rtype::getName(void)
{
    return "Rtype";
}

void Rtype::setRegistry(ecs::registry &reg)
{
    reg.register_component<RtypePlayer>();
}

void Rtype::setBroadcastCreate(std::function<void(ecs::entity const &e)>) {}
void Rtype::setBroadcastDelete(std::function<void(ecs::entity const &e)>) {}
void Rtype::setBroadcastUpdate(std::function<void(ecs::entity const &e)>) {}

std::vector<rtype::ClientAction> Rtype::getClientActionHandlers(void)
{
    return std::vector<rtype::ClientAction>();
}


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

void Rtype::processClientAction(ecs::registry &reg, std::string const &action, std::size_t client)
{
    std::optional<RtypePlayer> &p = reg.get_components<RtypePlayer>()[client];
    ecs::entity e = reg.entity_from_index(client);

    if (!p.has_value()) {
        reg.emplace_component<RtypePlayer>(e);
    }
    (void)action;
}


std::string RtypeGraphics::getName()
{
    return "Rtype";
}

std::map<int, std::string> RtypeGraphics::getInputsDefaultMap()
{
    return std::map<int, std::string>();
}

std::list<std::string> RtypeGraphics::getActions()
{
    return std::list<std::string>();
}

std::map<int, rtype::GraphicalElementData> RtypeGraphics::getGraphicalElements()
{
    return std::map<int, rtype::GraphicalElementData>();
}

void RtypeGraphics::setSystems(ecs::registry &reg)
{
    (void)reg;
}


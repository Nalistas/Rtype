/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RType
*/

#include "RType.hpp"

RType::RType()
{
}

RType::~RType()
{
}

void RType::initGameRegistry(ecs::registry &reg)
{
    
}

std::vector<rtype::ClientAction> RType::getClientActionHandlers(void) const
{
    return std::vector<rtype::ClientAction>();
}

std::vector<rtype::Background> RType::getBackgrounds(void) const
{
    return std::vector<rtype::Background>();
}

std::vector<rtype::Sprite> RType::getSprites(void) const
{
    return std::vector<rtype::Sprite>();
}

std::vector<std::string> RType::getMusics(void) const
{
    return std::vector<std::string>();
}

void RType::setUpdateSpeed(SpeedUpdater const &func)
{
}

void RType::setUpdatePosition(PositionUpdater const &func)
{
}

void RType::setCreate(Creater const &func)
{
}

void RType::setDelete(Deleter const &func)
{
}

void RType::setUseBackground(BackgroundChanger const &func)
{
}

void RType::setUseMusic(MusicChanger const &func)
{
}

std::size_t RType::createPlayer(void)
{
    return 0;
}

void RType::deletePlayer(std::size_t player_id)
{
}

rtype::IGame::ScreenUpdater RType::getScreenUpdater(void)
{
    return [](std::size_t client_id) {};
}

std::string RType::getName(void) const
{
    return "R-Type Game";
}


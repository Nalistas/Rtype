/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RType
*/

#include "RType.hpp"
#include "registry.hpp"
#include "Handlers/MoveHandlers.hpp"
#include "Component/Position.hpp"

RType::RType()
{
}

RType::~RType()
{
}

void RType::initGameRegistry(std::shared_ptr<ecs::registry> &reg)
{
    _registry = reg;
    _registry->register_component<Position>();
    _registry->register_component<Life>();
    _registry->register_component<Velocity>();
    _registry->register_component<SIDE>();
    _registry->register_component<Hitbox>();
}

std::vector<rtype::ClientAction> RType::getClientActionHandlers(void) const
{
    return std::vector<rtype::ClientAction>({
        {90, 1, std::make_unique<UpHandlers>()},
        {83, 1, std::make_unique<DownHandlers>()},
        {81, 1, std::make_unique<LeftHandlers>()},
        {68, 1, std::make_unique<RightHandlers>()}
    });
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
    _speedUpdater = func;
}

void RType::setUpdatePosition(PositionUpdater const &func)
{
    _positionUpdater = func;
}

void RType::setCreate(Creater const &func)
{
    _creater = func;
}

void RType::setDelete(Deleter const &func)
{
    _deleter = func;
}

void RType::setUseBackground(BackgroundChanger const &func)
{
    _backgroundChanger = func;
}

void RType::setUseMusic(MusicChanger const &func)
{
    _musicChanger = func;
}

std::size_t RType::createPlayer(void)
{
    if (!_registry) {
        return -1;
    }
    for (int i = 0; i < 4  ; i++) {
        if (_players.find(i) == _players.end()) {
            _players[i] = this->_registry->create_entity();
            return i;
        }
    }
    return -1;
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


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
    // createBackground();
    _registry->register_component<Position>();
    _registry->register_component<Life>();
    _registry->register_component<Speed>();
    _registry->register_component<SIDE>();
    _registry->register_component<Hitbox>();
}

// void RType::createBackground(void)
// {
//     ecs::entity newBackground = _registry->create_entity();
//     rtype::Background bg;
//     bg.path = "../bg.png";
//     bg.speed = 1;
//     bg.direction = rtype::Background::Direction::LEFT;
//     bg.loop = true;

//     // _registry->emplace_component<Background>(newBackground, bg);
//     _backgroundChanger(
// }


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
    // return std::vector<rtype::Background>({
    //     {.path("../bg.png"), .speed = 1, .direction = 0, .loop = true, .resize = true, .type = 1}
    // });
    return std::vector<rtype::Background>({
        rtype::Background{std::string("../bg.png"), 1, rtype::Background::LEFT, true, true, rtype::Background::MOVING}
    });
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
    return [this]() {
        for (auto player : _players) {
            auto position = _registry->get_components<Position>();
            for (auto [index, pos] : zipper(position)) {
                if (pos.has_value()) {
                    this->_positionUpdater(player.first, index, pos.value().x, pos.value().y);
                }
            }
            this->_backgroundChanger(player.first, 0);
        }
    };
}

std::string RType::getName(void) const
{
    return "R";
}


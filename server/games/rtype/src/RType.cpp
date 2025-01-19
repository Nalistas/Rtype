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
    _registry->register_component<Speed>();
    _registry->register_component<SIDE>();
    _registry->register_component<Hitbox>();
}

std::vector<rtype::ClientAction> RType::getClientActionHandlers(void) const
{
    return std::vector<rtype::ClientAction>({
        {90, 1, std::make_unique<UpHandlers>(_registry)},
        {83, 1, std::make_unique<DownHandlers>(_registry)},
        {81, 1, std::make_unique<LeftHandlers>(_registry)},
        {68, 1, std::make_unique<RightHandlers>(_registry)}
        // {32, 1, std::make_unique<ShootHandlers>()}
    });
}

std::vector<rtype::Background> RType::getBackgrounds(void) const
{
    return std::vector<rtype::Background>({
        rtype::Background{std::string("../bg.png"), 1, rtype::Background::LEFT, true, true, rtype::Background::MOVING}
    });
}

std::vector<rtype::Sprite> RType::getSprites(void) const
{
    return std::vector<rtype::Sprite>({
        rtype::Sprite{std::string("../ship.png"), 200, 200, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../enemy.png"), 200, 200, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../bullet.png"), 200, 200, 0, 0, 1, 0, 20, 20}
    });
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
            std::cout << "player " << i << " created" << std::endl;
            _registry->get_components<Position>().insert_at(_players[i], Position{0, 0});
            _creater(i, _players[i], 1, 0, 0, 0, 0);
            return i;
        }
    }
    return -1;
}

void RType::deletePlayer(std::size_t player_id)
{
    ecs::entity playerEntity = _registry->entity_from_index(player_id);
    _registry->delete_entity(playerEntity);
    _deleter(player_id, player_id);
}

rtype::IGame::ScreenUpdater RType::getScreenUpdater(void)
{
    return [this](std::size_t player_id) {
        auto position = _registry->get_components<Position>();
        if (this->_positionUpdater) {
            for (auto [index, pos] : zipper(position)) {
                if (pos.has_value()) {
                    this->_positionUpdater(player_id, index, pos.value().x, pos.value().y);
                }
            }
        }
        if (this->_backgroundChanger) {
            this->_backgroundChanger(player_id, 0);
        }
    };
}

std::string RType::getName(void) const
{
    return "R-Type";
}


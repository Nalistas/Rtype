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
#include "Systems/SystemMovement.hpp"
#include "Systems/SystemCollision.hpp"
#include "Systems/SystemCreateEnemy.hpp"
#include "Systems/SystemBroadcast.hpp"


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
    _registry->register_component<Damage>();
    _registry->add_system<Position, Speed>(SystemMovement());
    _registry->add_system<Position, Hitbox, Damage, Life, SIDE>(SystemCollision(_deleter));
    // _registry->add_system<>(SystemCreateEnemy(_creater));
    _registry->add_system<Speed, Position>(SystemBroadcast(_speedUpdater, _positionUpdater, _players));
}

std::vector<rtype::ClientAction> RType::getClientActionHandlers(void) const
{
    return std::vector<rtype::ClientAction>({
        {87, 1, std::make_unique<UpHandlers>(_registry)},
        {83, 1, std::make_unique<DownHandlers>(_registry)},
        {65, 1, std::make_unique<LeftHandlers>(_registry)},
        {68, 1, std::make_unique<RightHandlers>(_registry)},
        {87, 0, std::make_unique<UnUpDownHandlers>(_registry)},
        {83, 0, std::make_unique<UnUpDownHandlers>(_registry)},
        {65, 0, std::make_unique<UnRightLeftHandlers>(_registry)},
        {68, 0, std::make_unique<UnRightLeftHandlers>(_registry)}
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
        rtype::Sprite{std::string("../ship.png"), 50, 50, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../enemy.png"), 25, 25, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../bullet.png"), 10, 10, 0, 0, 1, 0, 20, 20}
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
            _registry->get_components<Position>().emplace_at(_players[i], Position{100, 0});
            _registry->get_components<Hitbox>().emplace_at(_players[i], Hitbox{20, 20});
            _registry->get_components<Life>().emplace_at(_players[i], Life{5});
            _registry->get_components<SIDE>().emplace_at(_players[i], SIDE::PLAYER);
            for (int j = 0; j < 4; j++) {
                if (j != i && _players.find(j) != _players.end()) {
                    _creater(_players[j], i, 0, 200, 200, 0, 0);
                }
            }
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
        for (auto [index, pos] : zipper(position)) {
            if (pos.has_value()) {
                std::cout << "player: " << player_id << " index: " << index << " position: " << pos.value().x << " " << pos.value().y << std::endl;
                this->_creater(player_id, index, 0, pos.value().x, pos.value().y, 0, 0);
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


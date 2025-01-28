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
#include "Systems/SystemShootEnemyBullet.hpp"
#include "Systems/SystemBroadcast.hpp"
#include "Handlers/ShootHandlers.hpp"



RType::RType()
{
    _lose = false;
}

RType::~RType()
{
}

void RType::initGameRegistry(std::shared_ptr<ecs::registry> &reg)
{
    _registry = reg;
    _registry->register_component<Position>();
    _registry->register_component<Score>();
    _registry->register_component<Life>();
    _registry->register_component<Speed>();
    _registry->register_component<SIDE>();
    _registry->register_component<Hitbox>();
    _registry->register_component<Damage>();
    _registry->register_component<Type>();
    _registry->add_system<Position, Speed>(SystemMovement(_players, _deleter, _lose));
    _registry->add_system<Position, Hitbox, Damage, Life, SIDE>(SystemCollision(_deleter, _players, _deadPlayers, _lose, _creater));
    _registry->add_system<>(SystemCreateEnemy(_creater, _players, _lose));
    _registry->add_system<Speed, Position>(SystemBroadcast(_speedUpdater, _positionUpdater, _players));
    _registry->add_system<Position, Type, SIDE>(SystemShootEnemyBullet(_creater, _players, _lose));
}

std::vector<rtype::ClientAction> RType::getClientActionHandlers(void) const
{
    return std::vector<rtype::ClientAction>({
        {87, 1, std::make_unique<UpHandlers>(_registry, _deadPlayers)},
        {83, 1, std::make_unique<DownHandlers>(_registry, _deadPlayers)},
        {65, 1, std::make_unique<LeftHandlers>(_registry, _deadPlayers)},
        {68, 1, std::make_unique<RightHandlers>(_registry, _deadPlayers)},
        {87, 0, std::make_unique<UnUpDownHandlers>(_registry, _deadPlayers)},
        {83, 0, std::make_unique<UnUpDownHandlers>(_registry, _deadPlayers)},
        {65, 0, std::make_unique<UnRightLeftHandlers>(_registry, _deadPlayers)},
        {68, 0, std::make_unique<UnRightLeftHandlers>(_registry, _deadPlayers)},
        {32, 1, std::make_unique<ShootHandlers>(_registry, _creater, _players, _deadPlayers)}
    });
}

std::vector<rtype::Background> RType::getBackgrounds(void) const
{
    return std::vector<rtype::Background>({
        rtype::Background{std::string("../assets/bg.png"), 1, rtype::Background::LEFT, true, true, rtype::Background::MOVING}
    });
}

std::vector<rtype::Sprite> RType::getSprites(void) const
{
    return std::vector<rtype::Sprite>({
        rtype::Sprite{std::string("../assets/ship.png"), 50, 50, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../assets/enemy.png"), 50, 50, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../assets/bullet.png"), 10, 10, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../assets/enemy2.png"), 50, 50, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../assets/bullet_enemy.png"), 10, 10, 0, 0, 1, 0, 20, 20},
        rtype::Sprite{std::string("../assets/lose_bg.png"), 300, 300, 0, 0, 1, 0, 20, 20}
    });
}

std::vector<std::string> RType::getMusics(void) const
{
    return std::vector<std::string>();
}

std::vector<rtype::Text> RType::getTexts(void) const
{
    return std::vector<rtype::Text>();
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

void RType::setTextUpdater(TextUpdater const &func)
{
    _textUpdater = func;
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
            _registry->get_components<Position>().emplace_at(_players[i], Position{100, 250});
            _registry->get_components<Hitbox>().emplace_at(_players[i], Hitbox{50, 50});
            _registry->get_components<Life>().emplace_at(_players[i], Life{5});
            _registry->get_components<SIDE>().emplace_at(_players[i], SIDE::PLAYER);
            for (int j = 0; j < 4; j++) {
                if (j != i && _players.find(j) != _players.end()) {
                    _creater(_players[j], _players[i], 0, 200, 200, 0, 0);
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
        auto positions = this->_registry->get_components<Position>();
        auto speeds = this->_registry->get_components<Speed>();
        uint8_t speed_x;
        uint8_t speed_y;
        for (auto [index, pos, speed] : zipper(positions, speeds)) {
            if (speed.has_value()) {
                speed_x = speed.value().x;
                speed_y = speed.value().y;
            } else {
                speed_x = 0;
                speed_y = 0;
            }
            if (pos.has_value()) {
                this->_creater(player_id, index, 0, pos.value().x, pos.value().y, speed_x, speed_y);
            }
        }
        if (this->_backgroundChanger) {
            this->_backgroundChanger(player_id, 0);
        }
        if (this->_textUpdater) {
            this->_textUpdater(player_id, 0, "Bonjour", 5, 200, 200 );
        }
    };
}

std::string RType::getName(void) const
{
    return "R-Type";
}


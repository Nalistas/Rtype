/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "registry.hpp"
#include "Rtype.hpp"

Rtype::Rtype()
{
    _reg.register_component<RtypePlayer>();
}

std::string Rtype::getName(void)
{
    return "R-Type Game";
}

void Rtype::setRegistry(ecs::registry &reg)
{
    _reg = reg;
}

void Rtype::setBroadcastCreate(std::function<void(ecs::entity const &e)> broadcastFunc)
{
    _broadcastCreate = broadcastFunc;
}

void Rtype::setBroadcastDelete(std::function<void(ecs::entity const &e)> broadcastFunc)
{
    _broadcastDelete = broadcastFunc;
}

void Rtype::setBroadcastUpdate(std::function<void(ecs::entity const &e)> broadcastFunc)
{
    _broadcastUpdate = broadcastFunc;
}

std::vector<rtype::ClientAction> Rtype::getClientActionHandlers(void)
{
    // Renvoyer les actions que les clients peuvent envoyer (par exemple mouvement, tir)
    return {};  // Implémenter les handlers ici
}

size_t Rtype::createPlayer(void)
{
    ecs::entity newPlayer = _reg.create_entity();
    RtypePlayer player;

    player.setPosition(0, 0);
    player.setSpeed(0, 0);
    player.setHealth(50);

    _players[newPlayer] = player;
    _broadcastCreate(newPlayer);

    return newPlayer;
}

void Rtype::deletePlayer(size_t id)
{
    if (_players.find(id) != _players.end()) {
        ecs::entity playerEntity = _reg.entity_from_index(id);
        _players.erase(id);
        _reg.delete_entity(playerEntity);
        _broadcastDelete(playerEntity);
    }
}

void Rtype::updatePlayer(size_t id, std::size_t x, std::size_t y)
{
    if (_players.find(id) != _players.end()) {
        auto &player = _players[id];
        player.setPosition(x, y);
        ecs::entity playerEntity = _reg.entity_from_index(id);
        _broadcastUpdate(playerEntity);
    }
}

size_t Rtype::createEnemy()
{
    ecs::entity newEnemy = _reg.create_entity();
    RtypeEnemy enemy;

    enemy.setPosition(0, 0);
    enemy.setSpeed(0, 0);
    enemy.setHealth(10);

    _enemies[newEnemy] = enemy;
    _broadcastCreate(newEnemy);

    return newEnemy;
}

void Rtype::createBullet()
{
    // Crée une balle tirée par un joueur ou un ennemi


}

void Rtype::createBackground()
{
    // Crée un fond d'écran ou défilement de l'arrière-plan
}

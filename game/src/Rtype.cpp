/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "registry.hpp"
#include "GraphicsPrimitives.hpp"
#include "Rtype.hpp"

Rtype::Rtype() : _reg(nullptr), _broadcastCreate(nullptr), _broadcastDelete(nullptr), _broadcastUpdate(nullptr) {}


std::string Rtype::getName(void)
{
    return "R-Type Game";
}

void Rtype::setRegistry(ecs::registry *reg)
{
    _reg = reg;
    // ici aadd_system + register_component + toutes les fonction pour paramétrer le registry **DU SERVER**
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
    ecs::entity newPlayer = _reg->create_entity();
    graphics_interface::Sprite sprite;
    sprite.speed_x = 0;
    sprite.speed_y = 0;
    sprite.pos_x = 0;
    sprite.pos_y = 0;
    sprite.path = "./orange.png";

    _reg->emplace_component<graphics_interface::Sprite>(newPlayer, sprite);

    /*
    --dans le setRegistry (qui sera renommé)-- 
    register_component<Health>()
    register_component<Sprite>() -- déjà fait dans le server

    -- ICI --
    _reg.emplace_component<Health>(newPlayer, health) // class health int
    _reg.emplace_component<Sprite>(newPlayer, Sprite)
    _reg.emplace_component<Speed>(newPlayer, Speed)
    _reg.emplace_component<Position>(newPlayer, Pos)


    //

    1er system -> manageBullet
    2eme system -> computeSingleBullet

    manage_bullet {
        reg.run_single_system<Health, Sprite, Camp>(SystemComputeSingleBullet(bullet actuelle))
    }
    */

    // player.setPosition(0, 0);
    // player.setSpeed(0, 0);
    // player.setHealth(50);

    // _players[newPlayer] = player;
    _broadcastCreate(newPlayer);

    return newPlayer;
}

void Rtype::deletePlayer(size_t id)
{
    // if (_players.find(id) != _players.end()) {
    //     ecs::entity playerEntity = _reg.entity_from_index(id);
    //     // _players.erase(id);
    //     _reg.delete_entity(playerEntity);
    //     _broadcastDelete(playerEntity);
    // }
}

// void Rtype::updatePlayer(size_t id, std::size_t x, std::size_t y)
// {
//     if (_players.find(id) != _players.end()) {
//         auto &player = _players[id];
//         player.setPosition(x, y);
//         ecs::entity playerEntity = _reg.entity_from_index(id);
//         _broadcastUpdate(playerEntity);
//     }
// }

size_t Rtype::createEnemy()
{
    ecs::entity newEnemy = _reg->create_entity();
    // RtypeEnemy enemy;

    // enemy.setPosition(0, 0);
    // enemy.setSpeed(0, 0);
    // enemy.setHealth(10);

    // _enemies[newEnemy] = enemy;
    _broadcastCreate(newEnemy);

    return newEnemy;
}

void Rtype::createBullet()
{
    // Crée une balle tirée par un joueur ou un ennemi
    ecs::entity newBullet = _reg->create_entity();
    // RtypeBullet bullet;

    // bullet.setPosition(0, 0);
    // bullet.setSpeed(0, 0);

    // _bullets[newBullet] = bullet;
    _broadcastCreate(newBullet);

    // Implémenter le tir ici
}

void Rtype::createBackground()
{
    // Crée un fond d'écran ou défilement de l'arrière-plan
}

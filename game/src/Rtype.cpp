/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "registry.hpp"
#include "GraphicsPrimitives.hpp"
#include "Systems/SystemDeleteEnemy.hpp"
#include "Systems/SystemCreateEnemy.hpp"
#include "Actions/ActionMoveUp.hpp"
#include "Actions/ActionMoveUpReleased.hpp"
#include "Actions/ActionMoveDown.hpp"
#include "Actions/ActionMoveDownReleased.hpp"
#include "Actions/ActionMoveLeft.hpp"
#include "Actions/ActionMoveRight.hpp"
#include "Actions/ActionMoveRightReleased.hpp"
#include "Actions/ActionMoveLeftReleased.hpp"
#include "Actions/ActionCreateBullet.hpp"
#include "Systems/SystemManageBullets.hpp"
#include "Camp.hpp"
#include "Health.hpp"
#include "Rtype.hpp"
#include "Damage.hpp"
#include <iostream>

Rtype::Rtype() : _reg(nullptr), _broadcastCreate(nullptr), _broadcastDelete(nullptr), _broadcastUpdate(nullptr)
{
    _reg = std::make_shared<ecs::registry>();
}


std::string Rtype::getName(void)
{
    return "R-Type Game";
}

void Rtype::setRegistry(std::shared_ptr<ecs::registry> reg)
{
    _reg = reg;
    createBackground();
    _reg->register_component<Health>();
    _reg->register_component<Damage>();
    _reg->register_component<Camp>();
    std::cout << "adding system CreateEnemy" << std::endl;
    _reg->add_standalone_system(SystemCreateEnemy(_broadcastCreate));
    std::cout << "adding system DeleteEnemy" << std::endl;
    _reg->add_system<graphics_interface::Sprite, Camp>(SystemDeleteEnemy(_broadcastDelete));
    std::cout << "adding system ManageBullets" << std::endl;
    _reg->add_system<graphics_interface::Sprite, Camp, Damage>(SystemManageBullets(_broadcastDelete));

    // std::cout << "setRegistry" << std::endl;
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
    std::vector<rtype::ClientAction> actions;
    actions.push_back(rtype::ClientAction{265, 1, std::make_unique<ActionMoveUp>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{265, 0, std::make_unique<ActionMoveUpReleased>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{264, 1, std::make_unique<ActionMoveDown>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{264, 0, std::make_unique<ActionMoveDownReleased>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{263, 1, std::make_unique<ActionMoveLeft>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{263, 0, std::make_unique<ActionMoveLeftReleased>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{262, 1, std::make_unique<ActionMoveRight>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{262, 0, std::make_unique<ActionMoveRightReleased>(_reg, _broadcastUpdate)});
    actions.push_back(rtype::ClientAction{32, 1, std::make_unique<ActionCreateBullet>(_reg, _broadcastCreate)});
    return actions;  // Implémenter les handlers ici
}

size_t Rtype::createPlayer(void)
{
    ecs::entity newPlayer = _reg->create_entity();
    graphics_interface::Sprite sprite;
    sprite.speed_x = 0;
    sprite.speed_y = 0;

    srand(time(NULL));
    sprite.pos_x = rand() % (800- 500);
    sprite.pos_y = rand() % (600 - 500);
    sprite.offset_x = 0;
    sprite.offset_y = 0;
    sprite.nb_frames = 1;
    sprite.ms_per_frame = 0;
    sprite.size_x = 100;
    sprite.size_y = 100;
    sprite.text_rect_width = 0;
    sprite.text_rect_height = 0;
    sprite.path = "./sheep.png";

    _reg->emplace_component<graphics_interface::Sprite>(newPlayer, sprite);
    _reg->emplace_component<Camp>(newPlayer, 0);
    _reg->emplace_component<Health>(newPlayer, 100);

    /*

    Client -> entite

    [Client] -> [entite]


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
    ecs::entity playerEntity = _reg->entity_from_index(id);
    _reg->delete_entity(playerEntity);
    _broadcastDelete(playerEntity);
}

void Rtype::createBullet()
{
    ecs::entity newBullet = _reg->create_entity();
    // RtypeBullet bullet;

    // bullet.setPosition(0, 0);
    // bullet.setSpeed(0, 0);

    // _bullets[newBullet] = bullet;
    _broadcastCreate(newBullet);

    // Implémenter le tir
}

void Rtype::createBackground()
{
    ecs::entity newBackground = _reg->create_entity();
    graphics_interface::Background bg;
    bg.path = "./bg.png";
    bg.speed = 1;
    bg.direction = graphics_interface::BackgroundDirection::X;
    bg.repeat = true;

    _reg->emplace_component<graphics_interface::Background>(newBackground, bg);
    _broadcastCreate(newBackground);
}

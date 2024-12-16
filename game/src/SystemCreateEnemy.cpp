/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemCreateEnemy
*/

#include "SystemCreateEnemy.hpp"
#include "GraphicsPrimitives.hpp"
#include "Health.hpp"
#include <iostream>

SystemCreateEnemy::SystemCreateEnemy(std::function<void(ecs::entity const &)> broadcastCreate)
        : _broadcastCreate(broadcastCreate), _last_update(std::chrono::system_clock::now()), _elapsed_time(0)
{
}


SystemCreateEnemy::~SystemCreateEnemy()
{
}

void SystemCreateEnemy::operator()(ecs::registry &registry, ecs::entity const &e __attribute__((unused)))
{
    auto now = std::chrono::system_clock::now();
    _elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(now - this->_last_update).count();

    if (_elapsed_time >= TIME_INTERVAL) {
        ecs::entity newEnemy = registry.create_entity();

        srand(time(NULL));

        graphics_interface::Sprite enemySprite;
        enemySprite.pos_x = 700 + rand() % (800 - 700);
        enemySprite.pos_y = rand() % (600 - 213);
        enemySprite.offset_x = 0;
        enemySprite.offset_y = 0;
        enemySprite.nb_frames = 1;
        enemySprite.ms_per_frame = 0;
        enemySprite.size_x = 192;
        enemySprite.size_y = 213;
        enemySprite.text_rect_width = 0;
        enemySprite.text_rect_height = 0;
        enemySprite.speed_x = -1;
        enemySprite.speed_y = 0;
        enemySprite.path = "./enemy.png";

        std::cout << "create enemy at " << enemySprite.pos_x << std::endl;

        registry.emplace_component<graphics_interface::Sprite>(newEnemy, enemySprite);
        registry.emplace_component<Health>(newEnemy, 10);

        _broadcastCreate(newEnemy);

        _elapsed_time = 0;
        this->_last_update = now;
    }
}

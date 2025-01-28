/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCollision
*/

#include "Systems/SystemCollision.hpp"
#include "registry.hpp"
#include <iostream>
// #include <chrono>



SystemCollision::SystemCollision(rtype::IGame::Deleter const &deleter, std::unordered_map<std::size_t, std::size_t> &players, std::unordered_set<std::size_t> &deads, bool &lose, rtype::IGame::Creater const &creater, rtype::IGame::TextUpdater &_textUpdater, int &score)
    : _deleter(deleter), _players(players), _deads(deads), _lose(lose), _creater(creater), _textUpdater(_textUpdater), _score(score)
{
}

SystemCollision::~SystemCollision()
{
}

void SystemCollision::broadcast(std::size_t entity_deleted, ecs::registry &registry)
{
    std::size_t player_dead = 0;
    bool is_player_dead = false;

    for (auto it = _players.begin(); it != _players.end(); it++) {
        _deleter(it->second, entity_deleted);
        if (it->second == entity_deleted) {
            is_player_dead = true;
            player_dead = it->first;
        }
    }

    if (is_player_dead) {
        _deads.insert(player_dead);
        registry.get_components<Position>()[entity_deleted].reset();
        registry.get_components<Speed>()[entity_deleted].reset();
    } else {
        registry.delete_entity(registry.entity_from_index(entity_deleted));
        for (auto it = _players.begin(); it != _players.end(); it++) {
            _textUpdater(it->first, 0, "score: " + std::to_string(_score), 30, 25, 20);
        }
    }
}

void SystemCollision::operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Hitbox> &hitboxs, sparse_array<Damage> &damages, sparse_array<Life> &healths, sparse_array<SIDE> &sides)
{
    if (_lose) {
        return;
    }
    for (auto [index, position, hitbox, damage, health, side] : zipper(positions, hitboxs, damages, healths, sides)) {
        if (!side.has_value() || side.value() == SIDE::ENEMY) continue;
        if (!position.has_value() || !hitbox.has_value() || !side.has_value()) continue;
        int left = position->x - hitbox->width / 2;
        int right = position->x + hitbox->width / 2;
        int top = position->y - hitbox->height / 2;
        int bottom = position->y + hitbox->height / 2;
        for (auto [index2, position2, hitbox2, damage2, health2, side2] : zipper(positions, hitboxs, damages, healths, sides)) {
            if (index == index2 || !position2.has_value() || !hitbox2.has_value() || !side2.has_value()) continue;
            if (side2 == side) continue;

            int left2 = position2->x - hitbox2->width / 2;
            int right2 = position2->x + hitbox2->width / 2;
            int top2 = position2->y - hitbox2->height / 2;
            int bottom2 = position2->y + hitbox2->height / 2;

            if (left < right2 && right > left2 && top < bottom2 && bottom > top2) {
                if (damage.has_value() && health2.has_value()) {
                    if (side.value() == PLAYER) {
                        health2.value().life -= damage.value().damage;
                        if (health2.value().life <= 0) {
                            auto entity = registry.entity_from_index(index2);
                            _score += 1;
                            this->broadcast(entity, registry);
                        }
                    } else {
                        health.value().life -= damage2.value().damage;
                        if (health.value().life <= 0) {
                            auto entity = registry.entity_from_index(index);
                            this->broadcast(entity, registry);
                        }
                    }
                    this->broadcast(index, registry);
                    continue;
                }
                if (health.has_value() && damage2.has_value()) {
                    // std::cout << "collision" << std::endl;
                    if (side.value() == PLAYER) {
                        health.value().life -= damage2.value().damage;
                        if (health.value().life <= 0) {
                            auto entity = registry.entity_from_index(index);
                            this->broadcast(entity, registry);
                        }
                    } else {
                        health2.value().life -= damage.value().damage;
                        if (health.value().life <= 0) {
                            auto entity = registry.entity_from_index(index2);
                            this->broadcast(entity, registry);
                        }
                    }
                    this->broadcast(index2, registry);
                    continue;
                }
            }
        }
    }

    if (isEveryPlayerDead() == true) {
        _lose = true;
        for (auto player : _players) {
            for (auto [index, pos, side] : zipper(registry.get_components<Position>(), registry.get_components<SIDE>())) {
                if (pos.has_value() && side.has_value() && side.value() == SIDE::ENEMY) {
                    registry.delete_entity(registry.entity_from_index(index));  
                    _deleter(player.first, index);
                }
            }
            auto bg_lose = registry.create_entity();
            registry.get_components<Position>().emplace_at(bg_lose, Position{400, 250});
            _creater(player.first, bg_lose, 5, 400, 250, 0, 0);
        }
    }
}

bool SystemCollision::isEveryPlayerDead()
{
    return _deads.size() == _players.size() && _players.size() != 0;
}

bool SystemCollision::checkCollision(const Position &posA, const Hitbox &hitboxA, const Position &posB, const Hitbox &hitboxB)
{
    return (posA.x < posB.x + hitboxB.width &&
            posA.x + hitboxA.width > posB.x &&
            posA.y < posB.y + hitboxB.height &&
            posA.y + hitboxA.height > posB.y);
}

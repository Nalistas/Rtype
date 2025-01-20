/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCollision
*/

#include "Systems/SystemCollision.hpp"
#include "registry.hpp"


SystemCollision::SystemCollision(rtype::IGame::Deleter const &deleter, std::unordered_map<std::size_t, std::size_t> &players)
    : _deleter(deleter), _players(players)
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
        _players.erase(player_dead);
        _players[player_dead] = registry.create_entity();
    }
    registry.delete_entity(registry.entity_from_index(entity_deleted));
}

void SystemCollision::operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Hitbox> &hitboxs, sparse_array<Damage> &damages, sparse_array<Life> &healths, sparse_array<SIDE> &sides)
{
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
                    this->broadcast(index2, registry);
                    this->broadcast(index, registry);
                    continue;
                }
                if (health.has_value() && damage2.has_value()) {
                    this->broadcast(index, registry);
                    this->broadcast(index2, registry);
                    continue;
                }
            }
        }
    }
    // for (size_t i = 0; i < position.size(); i++) {
    //     if (!position[i].has_value() || !hitbox[i].has_value() || !side[i].has_value()) continue;

    //     const Position &posA = position[i].value();
    //     const Hitbox &hitboxA = hitbox[i].value();
    //     const SIDE &sideA = side[i].value();

    //     for (size_t j = 0; j < position.size(); j++) {
    //         if (i == j || !position[j].has_value() || !hitbox[j].has_value() || !side[j].has_value()) continue;

    //         const Position &posB = position[j].value();
    //         const Hitbox &hitboxB = hitbox[j].value();
    //         const SIDE &sideB = side[j].value();

    //         if (sideB == PLAYER && sideA == ENEMY) {
    //             if (checkCollision(posA, hitboxA, posB, hitboxB)) {
    //                 if (damage[i].has_value() && health[j].has_value()) {
    //                     health[j].value().life -= damage[i].value().damage;

    //                     if (health[j].value().life <= 0) {
    //                         auto entity = registry.entity_from_index(j);
    //                         this->broadcast(entity, registry);
    //                     }
    //                 }
    //             }
    //         }
    //     }
    // }
}

bool SystemCollision::checkCollision(const Position &posA, const Hitbox &hitboxA, const Position &posB, const Hitbox &hitboxB)
{
    return (posA.x < posB.x + hitboxB.width &&
            posA.x + hitboxA.width > posB.x &&
            posA.y < posB.y + hitboxB.height &&
            posA.y + hitboxA.height > posB.y);
}

/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** SystemCollision
*/

#include "Systems/SystemCollision.hpp"

SystemCollision::SystemCollision(rtype::IGame::Deleter deleter)
    : _deleter(deleter)
{
}

SystemCollision::~SystemCollision()
{
}

void SystemCollision::operator()(ecs::registry &registry, sparse_array<Position> &position, sparse_array<Hitbox> &hitbox, sparse_array<Damage> &damage, sparse_array<Life> &health, sparse_array<SIDE> &side)
{
    for (size_t i = 0; i < position.size(); i++) {
        if (!position[i].has_value() || !hitbox[i].has_value() || !side[i].has_value()) continue;

        const Position &posA = position[i].value();
        const Hitbox &hitboxA = hitbox[i].value();
        const SIDE &sideA = side[i].value();

        for (size_t j = 0; j < position.size(); j++) {
            if (i == j || !position[j].has_value() || !hitbox[j].has_value() || !side[j].has_value()) continue;

            const Position &posB = position[j].value();
            const Hitbox &hitboxB = hitbox[j].value();
            const SIDE &sideB = side[j].value();

            if (sideB == PLAYER && sideA == ENEMY) {
                if (checkCollision(posA, hitboxA, posB, hitboxB)) {
                    if (damage[i].has_value() && health[j].has_value()) {
                        health[j].value().life -= damage[i].value().damage;

                        // if (health[j].value().life <= 0) {
                        //     auto entity = registry.entity_from_index(j);
                        //     registry.delete_entity(entity);
                        //     // broadcast to all players
                        // }
                    }
                }
            }
        }
    }
}

bool SystemCollision::checkCollision(const Position &posA, const Hitbox &hitboxA, const Position &posB, const Hitbox &hitboxB)
{
    return (posA.x < posB.x + hitboxB.width &&
            posA.x + hitboxA.width > posB.x &&
            posA.y < posB.y + hitboxB.height &&
            posA.y + hitboxA.height > posB.y);
}

/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry
*/

#include "registry.hpp"
#include "entity.hpp"

ecs::entity ecs::registry::create_entity()
{
    if (this->_unused_entities.empty()) {
        auto e = entity(this->_total_entity_count);
        this->_total_entity_count++;
        return e;
    }

    // Retirer l'entité de _unused_entities et la retourner directement
    std::size_t entity = *this->_unused_entities.begin();
    this->_unused_entities.erase(this->_unused_entities.begin());
    return this->entity_from_index(entity);
}

ecs::entity ecs::registry::entity_from_index(std::size_t idx)
{
    return entity(idx);
}

void ecs::registry::delete_entity(entity const &e)
{
    for (auto &destructor : this->_destructors) {
        destructor.second(*this, e);
    }
    this->_unused_entities.insert(e);
}

void ecs::registry::run_systems(void)
{
    for (auto &system : this->_systems) {
        system(*this);
    }
}   
/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** registry
*/

#include "registry.hpp"
#include "entity.hpp"

entity registry::create_entity()
{
    if (this->_unused_entities.empty()) {
        this->_total_entity_count++;
        return entity(this->_total_entity_count);
    }
    return entity(this->_unused_entities.begin().operator*());
}

entity registry::entity_from_index(std::size_t idx)
{
    return entity(idx);
}

void registry::delete_entity(entity const &e)
{
    for (auto &destructor : this->_destructors) {
        destructor.second(*this, e);
    }
    this->_unused_entities.insert(e);
}


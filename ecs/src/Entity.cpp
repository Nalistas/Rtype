/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Entity
*/

#include "Entity.hpp"

Entity::Entity(size_t const &s) :
    _id(s)
{}

Entity::~Entity()
{}

Entity::operator size_t() const
{
    return _id;
}

bool Entity::operator==(Entity const &other) const
{
    return _id == other._id;
}

bool Entity::operator!=(Entity const &other) const
{
    return _id != other._id;
}

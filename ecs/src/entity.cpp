/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Entity
*/

#include "entity.hpp"

entity::entity(size_t const &s) :
    _id(s)
{}

entity::~entity()
{}

entity::operator size_t() const
{
    return _id;
}

bool entity::operator==(entity const &other) const
{
    return _id == other._id;
}

bool entity::operator!=(entity const &other) const
{
    return _id != other._id;
}

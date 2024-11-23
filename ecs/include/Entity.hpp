/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Entity
*/

#include <cstddef>

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_

class Entity {
    public:
        explicit Entity(size_t const &s);
        ~Entity();

        operator size_t() const;
        bool operator==(Entity const &other) const;
        bool operator!=(Entity const &other) const;

    private:
        size_t _id;
};

#endif /* !ENTITY_HPP_ */

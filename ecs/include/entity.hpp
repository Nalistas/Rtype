/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Entity
*/

#include <cstddef>

#ifndef ENTITY_HPP_
    #define ENTITY_HPP_


namespace ecs {


class entity {
    public:
        explicit entity(size_t const &s);
        ~entity();

        operator size_t() const;
        bool operator==(entity const &other) const;
        bool operator!=(entity const &other) const;

    private:
        size_t _id;
};


}

#endif /* !ENTITY_HPP_ */

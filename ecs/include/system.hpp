/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** system
*/

#include "sparse_array.hpp"

#ifndef SYSTEM_HPP_
    #define ECS_SYSTEM_HPP_

namespace ecs {

class registry;

template <class... Components>
class system {
    public:
        system() = default;
        virtual ~system() = default;

        virtual void operator()(sparse_array<Components>& ...) const = 0;
};

}

#endif /* !SYSTEM_HPP_ */

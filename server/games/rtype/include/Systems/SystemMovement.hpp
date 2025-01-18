/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** SystemMovement
*/

#include "isystem.hpp"
#include "sparse_array.hpp"
#include "Component/Position.hpp"

#ifndef SYSTEMMOVEMENT_HPP_
    #define SYSTEMMOVEMENT_HPP_

class SystemMovement : public ecs::isystem<Position, Speed> {
    public:
        SystemMovement();
        ~SystemMovement();

        void operator()(ecs::registry &registry, sparse_array<Position> &positions, sparse_array<Speed> &speeds) override;
    private:
        int64_t _ms_last_update;
};

#endif /* !SYSTEMMOVEMENT_HPP_ */

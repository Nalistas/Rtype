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


/**
 * @brief Base class for all the systems.
 * @tparam Components the components used by the system to process
 * @code
 * class MySystem : public ecs::system<MyComponent1, MyComponent2> { // inherit from ecs::system and use template
 *     void operator()(
 *              ecs::sparse_array<MyComponent1>& sa1,
 *              ecs::sparse_array<MyComponent2>& sa2) const
 *      {
 *         // do something
 *      }
 * };
 * @endcode
 */
template <class... Components>
class isystem {
    public:
        isystem() = default;
        virtual ~isystem() = default;

        virtual void operator()(sparse_array<Components>& ...) const = 0;
};

}

#endif /* !SYSTEM_HPP_ */

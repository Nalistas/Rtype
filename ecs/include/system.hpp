/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** system
*/

#ifndef SYSTEM_HPP_
    #define ECS_SYSTEM_HPP_

namespace ecs {

class system {
    public:
        system() = default;
        virtual ~system() = default;

        virtual void operator()() = 0;
};

}

#endif /* !SYSTEM_HPP_ */

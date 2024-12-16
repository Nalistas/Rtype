/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemBackground
*/

#include "isystem.hpp"
#include "Background.hpp"

#ifndef SYSTEMBACKGROUND_HPP_
    #define SYSTEMBACKGROUND_HPP_

class SystemBackground : public ecs::isystem<Background> {
    public:
        /**
         * @brief Construct a new System Background object
         * @param elpased_time the reference to the elpased time
         */
        SystemBackground(std::size_t const &elpased_time);

        /**
         * @brief Destroy the System Background object
         */
        ~SystemBackground();

        /**
         * @brief Call the system
         */
        void operator()(ecs::registry &r, ecs::entity const &e, Background &b) override;

    private:
        std::size_t const &_elpased_time;
};

#endif /* !SYSTEMBACKGROUND_HPP_ */

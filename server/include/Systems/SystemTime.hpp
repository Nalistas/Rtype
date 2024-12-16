/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** SystemTime
*/

#include "isystem.hpp"
#include <chrono>

#ifndef SYSTEMTIME_HPP_
    #define SYSTEMTIME_HPP_

class SystemTime : ecs::isystem<> {
    public:
        /**
         * @brief Construct a new System Time object
         */
        SystemTime(std::size_t &time_to_update);

        /**
         * @brief Destroy the System Time object
         */
        ~SystemTime();

        /**
         * @brief Call the system
         */
        void operator()(ecs::registry &r __attribute__((unused)), ecs::entity const &e __attribute__((unused))) override;

    private:
        std::chrono::time_point<std::chrono::system_clock> _last_update;
        std::size_t &_elpased_time;
};

#endif /* !SYSTEMTIME_HPP_ */

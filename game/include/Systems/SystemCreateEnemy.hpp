/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemCreateEnemy
*/

#include "isystem.hpp"
#include "registry.hpp"

#include <chrono>
#include <functional>

#ifndef SYSTEMCREATEENEMY_HPP_
#define SYSTEMCREATEENEMY_HPP_


class SystemCreateEnemy : public ecs::isystem<> {
public:
    SystemCreateEnemy(std::function<void(ecs::entity const &)> broadcastCreate);
    ~SystemCreateEnemy();

    void operator()(ecs::registry &registry, ecs::entity const &e __attribute__((unused)));

protected:
private:
    std::function<void(ecs::entity const &)> _broadcastCreate;
    std::chrono::time_point<std::chrono::system_clock> _last_update;
    std::size_t _elapsed_time;
    static constexpr std::size_t TIME_INTERVAL = 5000;
};

#endif /* !SystemCreateEnemy_HPP_ */

/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAutoDestructTimer
*/

#include "AutoDestructTimer.hpp"
#include "ecs.hpp"

#ifndef SYSTEMAUTODESTRUCTTIMER_HPP_
#define SYSTEMAUTODESTRUCTTIMER_HPP_

class SystemAutoDestructTimer {
    public:
        SystemAutoDestructTimer();
        ~SystemAutoDestructTimer();
        void operator()(ecs::registry &registry, ecs::entity const &e, AutoDestructTimer &auto_destruct_timer);

    protected:
    private:

};

#endif /* !SYSTEMAUTODESTRUCTTIMER_HPP_ */

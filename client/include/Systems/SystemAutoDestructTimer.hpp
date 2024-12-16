/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** SystemAutoDestructTimer
*/

#include "AutoDestructTimer.hpp"
#include "isystem.hpp"

#ifndef SYSTEMAUTODESTRUCTTIMER_HPP_
#define SYSTEMAUTODESTRUCTTIMER_HPP_

class SystemAutoDestructTimer : public ecs::isystem<AutoDestructTimer> {
    public:
        SystemAutoDestructTimer();
        ~SystemAutoDestructTimer();
        void operator()(ecs::registry &registry, ecs::entity const &e, AutoDestructTimer &auto_destruct_timer);

    protected:
    private:

};

#endif /* !SYSTEMAUTODESTRUCTTIMER_HPP_ */

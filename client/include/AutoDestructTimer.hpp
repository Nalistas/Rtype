/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** AutoDestructTimer
*/

#include <iostream>

#ifndef AUTODESTRUCTTIMER_HPP_
#define AUTODESTRUCTTIMER_HPP_

class AutoDestructTimer {
    public:
        AutoDestructTimer();
        ~AutoDestructTimer();
        void set_time_to_destruct(std::size_t time_to_destruct);
        void set_created_time(std::size_t created_time);
        std::size_t get_time_to_destruct();
        std::size_t get_created_time();

    protected:
    private:
        std::size_t _created_time;
        std::size_t _time_to_destruct;
};

#endif /* !AUTODESTRUCTTIMER_HPP_ */

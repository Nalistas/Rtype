/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_

class Health {
    public:
        Health(int health);
        ~Health();
        void setHealth(int health);
        int getHealth();

    protected:
    private:
        int _health;
};

#endif /* !HEALTH_HPP_ */

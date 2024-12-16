/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Damage
*/

#ifndef DAMAGE_HPP_
#define DAMAGE_HPP_

class Damage {
    public:
        Damage(int damage);
        ~Damage();
        void setDamage(int damage);
        int getDamage();

    protected:
    private:
        int _damage;
};

#endif /* !DAMAGE_HPP_ */

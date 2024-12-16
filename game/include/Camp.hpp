/*
** EPITECH PROJECT, 2024
** mirror-rtype
** File description:
** Camp
*/

#ifndef CAMP_HPP_
#define CAMP_HPP_

class Camp {
    public:
        Camp(bool enemy);
        ~Camp();
        bool getCamp();
        void setCamp(bool enemy);

    protected:
    private:
        bool enemy;
};

#endif /* !CAMP_HPP_ */

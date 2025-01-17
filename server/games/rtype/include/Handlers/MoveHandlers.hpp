/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "IGame.hpp"

#ifndef MOVEHANDLERS_HPP_
    #define MOVEHANDLERS_HPP_

class UpHandlers : public rtype::IClientActionHandler {
    public:
        UpHandlers();
        ~UpHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
};

class DownHandlers : public rtype::IClientActionHandler {
    public:
        DownHandlers();
        ~DownHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
};

class LeftHandlers : public rtype::IClientActionHandler {
    public:
        LeftHandlers();
        ~LeftHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
};

class RightHandlers : public rtype::IClientActionHandler {
    public:
        RightHandlers();
        ~RightHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
};


#endif /* !MOVEHANDLERS_HPP_ */

/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "IGame.hpp"
#include "registry.hpp"

#ifndef MOVEHANDLERS_HPP_
    #define MOVEHANDLERS_HPP_

class UpHandlers : public rtype::IClientActionHandler {
    public:
        UpHandlers(const std::shared_ptr<ecs::registry> &reg);
        ~UpHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
};

class DownHandlers : public rtype::IClientActionHandler {
    public:
        DownHandlers(const std::shared_ptr<ecs::registry> &reg);
        ~DownHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
};

class LeftHandlers : public rtype::IClientActionHandler {
    public:
        LeftHandlers(const std::shared_ptr<ecs::registry> &reg);
        ~LeftHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
};

class RightHandlers : public rtype::IClientActionHandler {
    public:
        RightHandlers(const std::shared_ptr<ecs::registry> &reg);
        ~RightHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
};


#endif /* !MOVEHANDLERS_HPP_ */

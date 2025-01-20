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

class UnUpDownHandlers : public rtype::IClientActionHandler {
    public:
        UnUpDownHandlers(const std::shared_ptr<ecs::registry> &reg);
        ~UnUpDownHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
};

class UnRightLeftHandlers : public rtype::IClientActionHandler {
    public:
        UnRightLeftHandlers(const std::shared_ptr<ecs::registry> &reg);
        ~UnRightLeftHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
};

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

class ShootHandlers : public rtype::IClientActionHandler {
    public:
        ShootHandlers(const std::shared_ptr<ecs::registry> &reg, rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players);
        ~ShootHandlers();

        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    private:
        std::shared_ptr<ecs::registry> _registry;
        rtype::IGame::Creater const &_creater;
        std::unordered_map<std::size_t, std::size_t> const &_players;
};


#endif /* !MOVEHANDLERS_HPP_ */

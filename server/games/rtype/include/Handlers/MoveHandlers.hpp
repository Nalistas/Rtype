/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** MoveHandlers
*/

#include "IGame.hpp"
#include "registry.hpp"
#include <unordered_set>

#ifndef MOVEHANDLERS_HPP_
    #define MOVEHANDLERS_HPP_

/**
 * @brief UnUpDownHandlers class to handle the up and down actions
 */
class UnUpDownHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new UnUpDownHandlers object
         * 
         * @param reg
         */
        UnUpDownHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &deads);
        ~UnUpDownHandlers();

        /** 
         * @brief UnUpDownHandlers
         * 
         * @param client 
         * @param mouse_x 
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_set<std::size_t> const &_deads;
};

/**
 * @brief UnRightLeftHandlers class to handle the right and left actions
 */
class UnRightLeftHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new UnRightLeftHandlers object
         * 
         * @param reg
         */
        UnRightLeftHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &_deads);
        ~UnRightLeftHandlers();

        /** 
         * @brief UnRightLeftHandlers
         * 
         * @param client 
         * @param mouse_x 
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_set<std::size_t> const &_deads;
};

/**
 * @brief UpHandlers class to handle the up action
 */
class UpHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new UpHandlers object
         * 
         * @param reg
         */
        UpHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &_deads);
        ~UpHandlers();

        /**
         * @brief UpHandlers
         * 
         * @param client 
         * @param mouse_x 
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_set<std::size_t> const &_deads;
};

/**
 * @brief DownHandlers class to handle the down action
 */
class DownHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new DownHandlers object
         * 
         * @param reg
         */
        DownHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &_deads);
        ~DownHandlers();

        /**
         * @brief DownHandlers
         * 
         * @param client
         * @param mouse_x
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_set<std::size_t> const &_deads;
};

/**
 * @brief LeftHandlers class to handle the left action
 */
class LeftHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new LeftHandlers object
         * 
         * @param reg
         */
        LeftHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &_deads);
        ~LeftHandlers();

        /**
         * @brief LeftHandlers
         * 
         * @param client
         * @param mouse_x
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_set<std::size_t> const &_deads;
};

/**
 * @brief RightHandlers class to handle the right action
 */
class RightHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new RightHandlers object
         * 
         * @param reg
         * @param deads
         */
        RightHandlers(const std::shared_ptr<ecs::registry> &reg, std::unordered_set<std::size_t> const &_deads);
        ~RightHandlers();

        /**
         * @brief RightHandlers
         * 
         * @param client
         * @param mouse_x
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;
    private:
        std::shared_ptr<ecs::registry> _registry;
        std::unordered_set<std::size_t> const &_deads;
};

/**
 * @brief ShootHandlers class to handle the shoot action
 */
class ShootHandlers : public rtype::IClientActionHandler {
    public:
        /**
         * @brief Construct a new ShootHandlers object
         * 
         * @param reg
         * @param creater
         * @param players
         */
        ShootHandlers(const std::shared_ptr<ecs::registry> &reg, rtype::IGame::Creater const &creater, std::unordered_map<std::size_t, std::size_t> const &players, std::unordered_set<std::size_t> const &_deads);
        ~ShootHandlers();

        /**
         * @brief ShootHandlers
         * 
         * @param client 
         * @param mouse_x 
         * @param mouse_y
         */
        void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) override;

    private:
        std::shared_ptr<ecs::registry> _registry;
        rtype::IGame::Creater const &_creater;
        std::unordered_map<std::size_t, std::size_t> const &_players;
        std::unordered_set<std::size_t> const &_deads;
};


#endif /* !MOVEHANDLERS_HPP_ */

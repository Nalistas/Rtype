/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Rtype
*/

#include "IGame.hpp"
#include "registry.hpp"
// #include "RtypePlayer.hpp"
// #include "RtypeEnemy.hpp"
// #include "RtypeBullet.hpp"
#include <vector>
#include <map>
#include <functional>
#include <memory>


#ifndef RTYPE_HPP_
    #define RTYPE_HPP_

class Rtype : public rtype::IGame {
    public:
        Rtype();
        ~Rtype() = default;

        std::string getName(void) override;

        void setRegistry(std::shared_ptr<ecs::registry> reg) override;

        void setBroadcastCreate(std::function<void(ecs::entity const &e)>) override;
        void setBroadcastDelete(std::function<void(ecs::entity const &e)>) override;
        void setBroadcastUpdate(std::function<void(ecs::entity const &e)>) override;

        std::vector<rtype::ClientAction> getClientActionHandlers(void) override;
        size_t createPlayer(void) override;
        void deletePlayer(size_t id) override;

    protected:
        size_t createEnemy();
        void createBullet();
        void createBackground();
        void updatePlayer(size_t id, std::size_t x, std::size_t y);

    private:
        std::shared_ptr<ecs::registry> _reg;
        std::function<void(ecs::entity const &)> _broadcastCreate;
        std::function<void(ecs::entity const &)> _broadcastDelete;
        std::function<void(ecs::entity const &)> _broadcastUpdate;
};

#endif /* !RTYPE_HPP_ */

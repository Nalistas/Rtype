/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** BackgroundSystem
*/

#include "common/ecs/include/isystem.hpp"
#include "common/protocol/include/Encoder.hpp"

#include <functional>

#ifndef BACKGROUNDSYSTEM_HPP_
    #define BACKGROUNDSYSTEM_HPP_

class BackgroundSystem : public ecs::isystem<rtype_protocol::Background> {
    public:
        BackgroundSystem(std::function<void());
        ~BackgroundSystem();
        
        void operator()(ecs::registry &r __attribute__((unused)), ecs::entity const &e, rtype_protocol::Background &b) override;

    protected:
    private:
};

#endif /* !BACKGROUNDSYSTEM_HPP_ */

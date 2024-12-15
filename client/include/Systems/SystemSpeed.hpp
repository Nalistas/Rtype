// /*
// ** EPITECH PROJECT, 2024
// ** mirror-rtype
// ** File description:
// ** SystemSpeed
// */

<<<<<<< HEAD
#include "Raylib/Sprite.hpp"
#include "isystem.hpp"
#include "Speed.hpp"

#ifndef SYSTEMSPEED_HPP_
    #define SYSTEMSPEED_HPP_

class SystemSpeed : public ecs::isystem<Speed, raylib::Sprite> {
    public:
         /**
         * @brief Construct a new System Speed object
         * @param elpased_time the reference to the elpased time
         */
        SystemSpeed(std::size_t const &elpased_time);
        ~SystemSpeed();
        void operator()(ecs::registry &registry, ecs::entity const &e, Speed &speed, raylib::Sprite &sprite);
=======
// #include "isystem.hpp"
// #include "Speed.hpp"
// #include "Raylib/Sprite.hpp"
// #include "isystem.hpp"

// #ifndef SYSTEMSPEED_HPP_
// #define SYSTEMSPEED_HPP_

// class SystemSpeed : public ecs::isystem<Speed, raylib::Sprite> {
//     public:
//          /**
//          * @brief Construct a new System Speed object
//          * @param elpased_time the reference to the elpased time
//          */
//         SystemSpeed(std::size_t const &elpased_time);
//         ~SystemSpeed();
//         void operator()(ecs::registry &registry __attribute__((unused)), ecs::entity const &e __attribute__((unused)), Speed &speed, raylib::Sprite &sprite);
>>>>>>> bf06f69d2789240dfa24cadddcf76c9bc0fd6c4a


//     protected:
//     private:
//         std::size_t const &_elpased_time;
// };

// #endif /* !SYSTEMSPEED_HPP_ */

/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IGame
*/

#include <string>
#include <unordered_map>

#ifndef IGAME_HPP_
    #define IGAME_HPP_

namespace ecs {
    class registry;
}

namespace rtype {
    class IGame {
        public:
            /**
             * @brief Destroy the IGame object
             */
            virtual ~IGame() = default;

            /**
             * @brief Get the name of the display
             * @return the name of the display
             */
            virtual std::string getName() = 0;

            /**
             * @brief set everything needed in the registry
             * @param registry the registry to set the component and the systems
             */
            virtual void setRegistry(ecs::registry &reg) = 0;

            /**
             * @brief process an action mabe by the client
             * @param reg the registry
             * @param 
             */
            virtual void processClientAction(ecs::registry &reg, std::string const &action, std::size_t client) = 0;
    };
}

#endif

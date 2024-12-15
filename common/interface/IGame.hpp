/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** IGame
*/

#include <string>
#include <unordered_map>
#include <functional>
#include <memory>
#include <array>

#ifndef IGAME_HPP_
    #define IGAME_HPP_

namespace ecs {
    class registry;
    class entity;
}

namespace rtype {

    class IClientActionHandler {
        public:
        // mettre des references dans le constructeur
            virtual ~IClientActionHandler() = default;

            virtual void operator()(std::size_t client) = 0;
    };

    struct ClientAction {
        std::size_t key;
        bool pressed;
        std::unique_ptr<IClientActionHandler> handler;
    };


    class IGame {
        public:
            /**
             * @brief Destroy the IGame object
             */
            virtual ~IGame() = default;


            ///////////////////////////////////////////////////////////////
            //      SETTERS
            ///////////////////////////////////////////////////////////////
            /// @name Setters
            /// @brief this section is used to broadcast change on the display to the clients ONLY
            /// @{

            /**
             * @brief Set the broadcast create function
             */
            virtual void setBroadcastCreate(std::function<void(ecs::entity const &e)>) = 0;

            /**
             * @brief Set the broadcast delete function
             */
            virtual void setBroadcastDelete(std::function<void(ecs::entity const &e)>) = 0;

            /**
             * @brief Set the broadcast update function
             */
            virtual void setBroadcastUpdate(std::function<void(ecs::entity const &e)>) = 0;

            /// @}

            /**
             * @brief Get the name of the display
             * @return the name of the display
             */
            virtual std::string getName() = 0;

            /**
             * @brief set everything needed in the registry, the systems and the components
             * @param registry the registry to set the component and the systems
             */
            virtual void setRegistry(ecs::registry *reg) = 0;

            /**
             * @brief Set the client action handler
             * @return the map of the client action handlers with the action id
             */
            virtual std::vector<ClientAction> getClientActionHandlers(void) = 0;

            /**
             * @brief Create a player
             * @return the id of the player
             */
            virtual size_t createPlayer(void) = 0;

            /**
             * @brief Delete a player
             * @param id the id of the player
             */
            virtual void deletePlayer(size_t id) = 0;
    };
}

/*
    S                   J
        -------------> OK -> exec action (broadcast)
        <------------- voila, pour moi c'est lui (size_t)

-> action client
    |
    V
    get size_t lie
    a l'endpoint
    |
    V
    recupere l'handler
    |
    V
    handler(client) -> J -> client
*/

#endif
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

            virtual void operator()(std::size_t client, unsigned int mouse_x, unsigned int mouse_y) = 0;
    };

    struct ClientAction {
        unsigned int key;
        bool pressed;
        std::unique_ptr<IClientActionHandler> handler;
    };


    struct Sprite {
        std::string path;
        uint32_t size_x;
        uint32_t size_y;
        uint32_t texture_rect_offset_x;
        uint32_t texture_rect_offset_y;
        uint32_t texture_rect_size_x;
        uint32_t texture_rect_size_y;
        uint8_t nb_frames;
        uint32_t ms_per_frame;
    };

    struct Background {
        std::string path;
        uint8_t speed;
        enum Direction {
            LEFT    = 0,
            RIGHT   = 1,
            UP      = 2,
            DOWN    = 3
        } direction;
        bool loop;
        bool resize;
        enum Type {
            STATIC  = 0,
            MOVING  = 1,
            PARALLAX = 2
        } type;
    };

    class IGame {
        public:
            /**
             * @brief Destroy the IGame objectint
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
            virtual void setUpdateSpeed(std::size_t client_id, std::size_t entity_id, uint8_t speed_x, uint8_t speed_y) = 0;

            /**
             * @brief Set the broadcast update function
             */
            virtual void setUpdatePosition(std::size_t client_id, std::size_t entity_id, int x, int y) = 0;

            /**
             * @brief Set the broadcast delete function
             */
            virtual void setCreate(std::size_t client_id, std::size_t entity_id, std::size_t entity_graphics_id, int x, int y, uint8_t speed_x, uint8_t speed_y) = 0;

            /**
             * @brief Set the broadcast delete function
             */
            virtual void setDelete(std::size_t client_id, std::size_t entity_id) = 0;

            /**
             * @brief Set the broadcast delete function
             */
            virtual void setUseBackground(std::size_t client_id, std::size_t background_id) = 0;

            /**
             * @brief Set the broadcast delete function
             */
            virtual void setUseMusic(std::size_t client_id, std::size_t music_id) = 0;

            /// @}

            ///////////////////////////////////////////////////////////////
            //      GETTERS
            ///////////////////////////////////////////////////////////////
            /// @name Getters
            /// @brief this section is used by the server to get the graphics used in the game
            /// @{

            /**
             * @brief Get the backgrounds used in the game
             * @return the vector of the backgrounds, we suppose that the id of the background is the same as the index
             */
            virtual std::vector<Background> const &getBackgrounds(void) const = 0;

            /**
             * @brief Get the sprites used in the game
             * @return the vector of the sprites, we suppose that the id of the sprite is the same as the index
             */
            virtual std::vector<Sprite> const &getSprites(void) const = 0;

            /**
             * @brief Get the music used in the game
             * @return the vector of the music, we suppose that the id of the music is the same as the index
             */
            virtual std::vector<std::string> const &getMusics(void) const = 0;

            /**
             * @brief Get the name of the display
             * @return the name of the display
             */
            virtual std::string const &getName() const = 0;

            /// @}

            ///////////////////////////////////////////////////////////////
            //      OTHERS
            ///////////////////////////////////////////////////////////////

            /**
             * @brief set everything needed in the registry, the systems and the components
             * @param registry the registry to set the component and the systems
             */
            virtual void setRegistry(ecs::registry &reg) = 0;

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
/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include "registry.hpp"
#include "Raylib/Window.hpp"
#include "Raylib/AudioDevice.hpp"
#include "Background.hpp"
#include "Raylib/RayMusic.hpp"
#include "Raylib/RaySound.hpp"
#include "Raylib/Sprite.hpp"
#include "Speed.hpp"
#include "Animation.hpp"
#include "AsioApi.hpp"
#include "AutoDestructTimer.hpp"

#include <unordered_map>

#ifndef CORE_HPP_
    #define CORE_HPP_

enum class EntityOperation {
    CREATE = 1,
    REMOVE = 2,
    UPDATE = 3,
    ACTION = 4
};

enum class EntityType {
    BACKGROUND = 1,
    MUSIC = 2,
    SOUND = 3,
    SPRITE = 4
};

class Core {
    public:
        /**
         * @brief Construct a new Core object
         * @param win_width The width of the window
         * @param win_height The height of the window
         */
        Core(std::size_t win_width, std::size_t win_height);

        /**
         * @brief Destroy the Core object
         */
        ~Core();

        /**
         * @brief Run the core
         * @return the exit code
         */
        int run(void);

        /**
         * @brief Process a message
         */
        void process_message(const std::vector<char> &message);

        /**
         * @brief Update the sprite component
         * @param entity The entity
         * @param entity_data The entity data
         */
        void update_sprite_component(ecs::entity entity, const std::vector<char> &entity_data);

        /**
         * @brief Update the background component
         * @param entity The entity
         * @param entity_data The entity data
         */
        void update_background_component(ecs::entity entity, const std::vector<char> &entity_data);

        /**
         * @brief Update the music component
         * @param entity The entity
         * @param entity_data The entity data
         */
        void update_music_component(ecs::entity entity, const std::vector<char> &entity_data);

        /**
         * @brief Update the sound component
         * @param entity The entity
         * @param entity_data The entity data
         */
        void update_sound_component(ecs::entity entity, const std::vector<char> &entity_data);


    private:

        /**
         * @brief Create an entity
         * @param message The message
         */
        void create_entity(std::vector<char> &message);

        /**
         * @brief Delete an entity
         * @param message The message
         */
        void delete_entity(std::vector<char> &message);

        /**
         * @brief Update an entity
         * @param message The message
         */
        void update_entity(std::vector<char> &message);

        /**
         * @brief Handle the creation of an entity
         * @param entity_type The type of the entity
         * @param entity_id The id of the entity
         * @param entity_data The data of the entity
         */
        void handle_create_entity(EntityType entity_type, std::size_t entity_id, const std::vector<char> &entity_data);

        /**
         * @brief Set the actions
         * @param actions The actions
         */
        void set_actions(std::vector<char> const &actions);

        /**
         * @brief send an action to the server
         * @param id_action The id of the action
         * @param pressed The pressed state of the action
         */
        void send_action(unsigned int id_action);



        //////////////////////////////////////////
        //
        // ATTRIBUTES
        //
        //////////////////////////////////////////

        raylib::Window _window;
        raylib::AudioDevice audioDevice;
        ecs::registry _registry;


                            // key code, id_action
        std::unordered_map<unsigned int, unsigned int> _on_key_pressed;
        std::unordered_map<unsigned int, unsigned int> _on_key_released;


        rtype_protocol::AsioApi _api;


        //////////////////////////////////////////
        //
        // MAP OF FUNCTIONS
        //
        //////////////////////////////////////////

        std::unordered_map<EntityOperation, std::function<void(std::vector<char> &message)>> _operation_functions = {
            {EntityOperation::CREATE, [this](std::vector<char> &message){create_entity(message);}},
            {EntityOperation::REMOVE, [this](std::vector<char> &message){delete_entity(message);}},
            {EntityOperation::UPDATE, [this](std::vector<char> &message){update_entity(message);}},
            {EntityOperation::ACTION, [this](std::vector<char> &message){set_actions(message);}}
        };


       std::unordered_map<EntityType, std::function<void(ecs::entity, const std::vector<char>&)>> _create_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::vector<char>& data) {
                graphics_interface::Background background;
                background.decode(data);
                _registry.emplace_component<Background>(e);
                _registry.get_components<Background>()[e]->setComponent(background);
            }},
            {EntityType::MUSIC, [this](ecs::entity e, const std::vector<char>& data) {
                graphics_interface::Music music;
                music.decode(data);
                raylib::RayMusic rayMusic(music.path);
                _registry.emplace_component<raylib::RayMusic>(e, rayMusic);
            }},
            {EntityType::SOUND, [this](ecs::entity e, const std::vector<char>& data) {
                graphics_interface::Sound sound;
                sound.decode(data);
                raylib::RaySound raySound(sound.path);
                _registry.emplace_component<raylib::RaySound>(e, raySound);
            }},
            {EntityType::SPRITE, [this](ecs::entity e, const std::vector<char>& data) {
                graphics_interface::Sprite sprite;
                sprite.decode(data);
                _registry.emplace_component<raylib::Sprite>(e);
                _registry.get_components<raylib::Sprite>()[e]->setComponent(sprite);

                if (sprite.speed_x != 0 || sprite.speed_y != 0) {
                    raylib::Vector2 spe;
                    spe.x = sprite.speed_x;
                    spe.y = sprite.speed_y;
                    _registry.emplace_component<Speed>(e);
                    _registry.get_components<Speed>()[e]->setSpeed(spe);
                }
            }}
        };


        std::unordered_map<EntityType, std::function<void(ecs::entity, const std::vector<char>&)>> _update_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::vector<char> &data) {update_background_component(e, data);}},
            {EntityType::MUSIC, [this](ecs::entity e, const std::vector<char> &data) {update_music_component(e, data);}},
            {EntityType::SOUND, [this](ecs::entity e, const std::vector<char> &data) {update_sound_component(e, data);}},
            {EntityType::SPRITE, [this](ecs::entity e, const std::vector<char> &data) {update_sprite_component(e, data);}}
        };
        std::size_t time;
};



#endif /* !CORE_HPP_ */

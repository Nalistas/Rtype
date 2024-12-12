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
#include "Encoder.hpp"

#include <unordered_map>

#ifndef CORE_HPP_
    #define CORE_HPP_

enum class EntityOperation {
    CREATE = 1,
    DELETE = 2,
    UPDATE = 3
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



        raylib::Window _window;
        raylib::AudioDevice audioDevice;
        ecs::registry _registry;
        rtype_protocol::Encoder _encoder;


        std::unordered_map<EntityOperation, std::function<void(std::vector<char> &message)>> _operation_functions = {
            {EntityOperation::CREATE, [this](std::vector<char> &message){create_entity(message);}},
            {EntityOperation::DELETE, [this](std::vector<char> &message){delete_entity(message);}},
            {EntityOperation::UPDATE, [this](std::vector<char> &message){update_entity(message);}}
        };


       std::unordered_map<EntityType, std::function<void(ecs::entity, const std::vector<char>&)>> _create_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::vector<char>& data) {
                rtype_protocol::Background background = _encoder.decodeBackground(data);
                Background bg;
                _registry.emplace_component<Background>(e, bg);
                _registry.get_components<Background>()[e]->setComponent(background);
            }},
            {EntityType::MUSIC, [this](ecs::entity e, const std::vector<char>& data) {
                rtype_protocol::Music music = _encoder.decodeMusic(data);
                raylib::RayMusic rayMusic(music.path);
                _registry.emplace_component<raylib::RayMusic>(e, rayMusic);
            }},
            {EntityType::SOUND, [this](ecs::entity e, const std::vector<char>& data) {
                rtype_protocol::Sound sound = _encoder.decodeSound(data);
                raylib::RaySound raySound(sound.path);
                _registry.emplace_component<raylib::RaySound>(e, raySound);
            }},
            {EntityType::SPRITE, [this](ecs::entity e, const std::vector<char>& data) {
                rtype_protocol::Sprite sprite = _encoder.decodeSprite(data);
                raylib::Sprite raySprite;
                _registry.emplace_component<raylib::Sprite>(e, raySprite);
                _registry.get_components<raylib::Sprite>()[e]->setComponent(sprite);
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

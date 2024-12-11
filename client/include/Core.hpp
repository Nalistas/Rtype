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
         * @brief Updates the texture component of the specified entity.
         * 
         * @tparam T The type of the component to update.
         * @param entity The entity whose texture component is to be updated.
         * @param texture_data The new texture data to set for the component.
         */
        template <typename T>
        void update_texture_component(ecs::entity entity, const std::string &texture_data);

        /**
         * @brief Updates the source component of the specified entity.
         * 
         * @tparam T The type of the component to update.
         * @param entity The entity whose source component is to be updated.
         * @param source_data The new source data to set for the component.
         */
        template <typename T>
        void update_source_component(ecs::entity entity, const std::string &source_data);

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


        std::unordered_map<EntityOperation, std::function<void(std::vector<char> &message)>> _operation_functions = {
            {EntityOperation::CREATE, [this](std::vector<char> &message){create_entity(message);}},
            {EntityOperation::DELETE, [this](std::vector<char> &message){delete_entity(message);}},
            {EntityOperation::UPDATE, [this](std::vector<char> &message){update_entity(message);}}
        };


        std::unordered_map<EntityType, std::function<void(ecs::entity, const std::string&)>> _create_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<Background>(e, data); }},
            {EntityType::MUSIC, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<raylib::RayMusic>(e, data); }},
            {EntityType::SOUND, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<raylib::RaySound>(e, data); }},
            {EntityType::SPRITE, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<raylib::Sprite>(e, data); }}
        };


        std::unordered_map<EntityType, std::function<void(ecs::entity, const std::string&)>> _update_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::string &data) {update_texture_component<Background>(e, data);}},
            {EntityType::SPRITE, [this](ecs::entity e, const std::string &data) {update_texture_component<raylib::Sprite>(e, data);}},
            {EntityType::MUSIC, [this](ecs::entity e, const std::string &data) {update_source_component<raylib::RayMusic>(e, data);}},
            {EntityType::SOUND, [this](ecs::entity e, const std::string &data) {update_source_component<raylib::RaySound>(e, data);}}
        };
        std::size_t time;
};



#endif /* !CORE_HPP_ */

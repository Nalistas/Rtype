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

#include <map>

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
        Core(std::size_t win_width, std::size_t win_height);
        ~Core();

        int run(void);
        void process_message(const std::string &message);
        void create_entity(std::string &message);
        void delete_entity(std::string &message);
        void update_entity(std::string &message);
        void handle_create_entity(EntityType entity_type, std::size_t entity_id, const std::string &entity_data);
        template <typename T>
        void update_texture_component(ecs::entity entity, const std::string &texture_data);
        template <typename T>
        void update_source_component(ecs::entity entity, const std::string &source_data);

    private:
        raylib::Window _window;
        raylib::AudioDevice audioDevice;
        ecs::registry _registry;
        std::map<EntityOperation, std::function<void(std::string &message)>> _operation_functions = {
            {EntityOperation::CREATE, [this](std::string &message){create_entity(message);}},
            {EntityOperation::DELETE, [this](std::string &message){delete_entity(message);}},
            {EntityOperation::UPDATE, [this](std::string &message){update_entity(message);}}
        };
        std::map<EntityType, std::function<void(ecs::entity, const std::string&)>> _create_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<Background>(e, data); }},
            {EntityType::MUSIC, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<raylib::RayMusic>(e, data); }},
            {EntityType::SOUND, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<raylib::RaySound>(e, data); }},
            {EntityType::SPRITE, [this](ecs::entity e, const std::string &data) { _registry.emplace_component<raylib::Sprite>(e, data); }}
        };
        std::map<EntityType, std::function<void(ecs::entity, const std::string&)>> _update_entity_functions = {
            {EntityType::BACKGROUND, [this](ecs::entity e, const std::string &data) {update_texture_component<Background>(e, data);}},
            {EntityType::SPRITE, [this](ecs::entity e, const std::string &data) {update_texture_component<raylib::Sprite>(e, data);}},
            {EntityType::MUSIC, [this](ecs::entity e, const std::string &data) {update_source_component<raylib::RayMusic>(e, data);}},
            {EntityType::SOUND, [this](ecs::entity e, const std::string &data) {update_source_component<raylib::RaySound>(e, data);}}
        };
        std::size_t time;
};



#endif /* !CORE_HPP_ */

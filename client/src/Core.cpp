/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Core
*/

#include "Core.hpp"

#include "Systems/SystemTime.hpp"
#include "Systems/SystemBackground.hpp"
#include "Systems/SystemSprite.hpp"

#include "isystem.hpp"
#include "AsioApi.hpp"
#include "entity.hpp"
#include "registry.hpp"


Core::Core(std::size_t win_width, std::size_t win_height):
    _window(win_width, win_height)
{
    _registry.register_component<raylib::RayMusic>();
    _registry.register_component<raylib::RaySound>();
    _registry.register_component<Background>();
    _registry.register_component<raylib::Sprite>();

    _registry.add_standalone_system(SystemTime(this->time));
    _registry.add_system<Background>(SystemBackground(this->time));
    _registry.add_system<raylib::Sprite>(SystemSprite());

}

Core::~Core()
{
}

class SystemTest : public ecs::isystem<> {
    public:
        void operator()(ecs::registry &registry, ecs::entity const &e) override
        {
            (void)registry;
            (void)e;
        }
};

void Core::process_message(const std::vector<char> &message) 
{
    if (message.empty()) return;
    std::cout << "Traitement du message : ";
    for (char c : message) std::cout << c;
    std::cout << std::endl;

    EntityOperation op_code = static_cast<EntityOperation>(message[0]);

    auto it = _operation_functions.find(op_code);
    if (it != _operation_functions.end()) {
        it->second(const_cast<std::vector<char> &>(message));
    } else {
        std::cerr << "Op-code inconnu ou invalide : " << static_cast<int>(op_code) << std::endl;
    }
}

void Core::handle_create_entity(EntityType entity_type, std::size_t entity_id, const std::vector<char> &entity_data)
{
    ecs::entity entity = _registry.entity_from_index(entity_id);

    std::cout << "Création de l'entité avec l'id " << entity_id << std::endl;

    auto it = _create_entity_functions.find(entity_type);
    if (it != _create_entity_functions.end()) {
        it->second(entity, std::string(entity_data.begin(), entity_data.end()));
        std::cout << "Création de l'entité avec l'id " << entity_id << " fini !" << std::endl;
    } else {
        std::cerr << "Type d'entité inconnu : " << static_cast<int>(entity_type) << std::endl;
    }
}

void Core::create_entity(std::vector<char> &message)
{
    EntityType entity_type = static_cast<EntityType>(message[1]);
    std::size_t entity_id = static_cast<std::size_t>(message[2]);
    std::vector<char> entity_data(message.begin() + 3, message.end());

    handle_create_entity(entity_type, entity_id, entity_data);
}

void Core::delete_entity(std::vector<char> &message) 
{
    int entity_id = static_cast<int>(message[1]);

    std::cout << "Suppression de l'entité avec l'id " << entity_id << std::endl;
    ecs::entity entity = _registry.entity_from_index(entity_id);
    _registry.delete_entity(entity);
}

template <typename T>
void Core::update_texture_component(ecs::entity entity, const std::string &texture_data)
{
    auto &component = _registry.get_components<T>()[entity];
    if (component.has_value()) {
        component->set_texture(texture_data);
    }
}

template <typename T>
void Core::update_source_component(ecs::entity entity, const std::string &source_data)
{
    auto &component = _registry.get_components<T>()[entity];
    if (component.has_value()) {
        component->set_source(source_data);
    }
}

void Core::update_entity(std::vector<char> &message) {
    EntityType entity_type = static_cast<EntityType>(message[1]);
    std::size_t entity_id = static_cast<std::size_t>(message[2]);
    std::vector<char> entity_data(message.begin() + 3, message.end());

    ecs::entity entity = _registry.entity_from_index(entity_id);
    auto it = _update_entity_functions.find(entity_type);
    if (it != _update_entity_functions.end()) {
        it->second(entity, std::string(entity_data.begin(), entity_data.end()));
    } else {
        std::cerr << "Type d'entité inconnu : " << static_cast<int>(entity_type) << std::endl;
    }
}

int Core::run(void)
{
    ecs::entity background = _registry.create_entity();
    _registry.emplace_component<Background>(background);
    rtype_protocol::AsioApi client;
    client.connect("localhost");

    while (_window.is_running()) {
        if (client.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = client.get_data();
            std::cout << "Réception de données : ";
            for (std::size_t i = 0; i < data.data.size(); i++) {
                std::cout <<  static_cast<int>(data.data[i]) << " ";
            }
            std::cout << "from " << data.sender_endpoint.address() 
                      << ":" << data.sender_endpoint.port() << std::endl;
            std::cout << std::endl;

            process_message(data.data);
        }

        _window.start_drawing();
        _registry.run_systems();
        if (_window.is_key(raylib::Window::BUTTON_STATE::PRESSED, KEY_SPACE)) {
            _registry.run_single_standalone_system(SystemTest());
        }
        _window.end_drawing();
    }
    return 0;
}

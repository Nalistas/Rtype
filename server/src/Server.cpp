/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include <string>

#include "SafeDirectoryLister.hpp"
#include "DLLoader.hpp"
#include "IGame.hpp"

std::size_t endpoint_hash_class::operator()(const udp::endpoint &ep) const {
    return std::hash<std::string>()(ep.address().to_string() + ":" + std::to_string(ep.port()));
}


Server::Server() 
    : _api()
{


    SafeDirectoryLister sd;
    sd.open(".", false);

    #ifdef WIN32
        _dll.open("./libRtype.dll");
    #else
        _dll.open("./libRtype.so");
    #endif
    _game = _dll.getSym("gameElement");

    _registry.register_component<rtype_protocol::Sprite>();
    _registry.register_component<rtype_protocol::Background>();
    _registry.register_component<rtype_protocol::Music>();
    _registry.register_component<rtype_protocol::Sound>();

    _game->setRegistry(_registry);
    _game->setBroadcastCreate(std::bind(&Server::broadcastCreate, this, std::placeholders::_1));
    _game->setBroadcastDelete(std::bind(&Server::broadcastDelete, this, std::placeholders::_1));
    _game->setBroadcastUpdate(std::bind(&Server::broadcastUpdate, this, std::placeholders::_1));

    _api.start_server("5000");
}

Server::~Server() 
{
}

int Server::loop() 
{
    std::string bgname = "./orange.png";
    rtype_protocol::Sprite sp;
    sp.pos_x = 100;
    sp.pos_y = 100;
    sp.size_x = 100;
    sp.size_y = 100;
    sp.path = bgname;
    sp.offset_x = 0;
    sp.offset_y = 0;
    sp.speed_x = 0;
    sp.speed_y = 0;
    sp.text_rect_width = 0;
    sp.text_rect_height = 0;
    sp.nb_frames = 0;
    sp.ms_per_frame = 0;
    sp.auto_destroy = 0;

    int total_size = 0;
    while (true) {
        if (_api.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = _api.get_data();

            if (_clients.find(data.sender_endpoint) == _clients.end()) {
                _clients.insert(data.sender_endpoint);
                std::cout << "Nouveau client ajouté : " 
                        << data.sender_endpoint.address().to_string()
                        << ":" << data.sender_endpoint.port() << std::endl;

                data.data = _encoder.encode(sp);

                data.data.insert(data.data.begin(), static_cast<char>(2));
                data.data.insert(data.data.begin(), static_cast<char>(EntityType::SPRITE));
                data.data.insert(data.data.begin(), static_cast<char>(EntityOperation::CREATE));
                total_size = data.data.size();
                data.data.insert(data.data.begin(), static_cast<char>(total_size));
                _api.reply_to(data);
            }
        }
    }

    return 0;
}


void Server::broadcastDelete(ecs::entity entity)
{
    rtype_protocol::AsioApi::UDP_DATA data;

    data.data = std::vector<char>();
    data.data.resize(2 + sizeof(entity));
    data.data[0] = static_cast<char>(3);
    data.data[1] = static_cast<char>(EntityOperation::REMOVE);

    memcpy(&data.data[2], &entity, sizeof(entity));

    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        data.sender_endpoint = *it;
        _api.reply_to(data);
    }
}

void Server::broadcast(char op_code, char entity_type, std::vector<char> const &data)
{
    rtype_protocol::AsioApi::UDP_DATA client_data;
    client_data.data = data;

    client_data.data.insert(client_data.data.begin(), static_cast<char>(op_code));
    client_data.data.insert(client_data.data.begin(), entity_type);

    for (auto it = _clients.begin(); it != _clients.end(); it++) {
        client_data.sender_endpoint = *it;
        _api.reply_to(client_data);
    }
}

void Server::broadcastCreate(ecs::entity entity)
{
    rtype_protocol::AsioApi::UDP_DATA data;
    char op_code = static_cast<char>(EntityOperation::CREATE);
    char entity_type;
    char id = static_cast<char>(entity);

    auto music = _registry.get_components<rtype_protocol::Music>()[entity];
    if (music.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*music));
    }
    auto sound = _registry.get_components<rtype_protocol::Sound>()[entity];
    if (sound.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*sound));
    }
    auto sprite = _registry.get_components<rtype_protocol::Sprite>()[entity];
    if (sprite.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*sprite));
    }
    auto bg = _registry.get_components<rtype_protocol::Background>()[entity];
    if (bg.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*bg));
    }
}

void Server::broadcastUpdate(ecs::entity entity)
{
    rtype_protocol::AsioApi::UDP_DATA data;
    char op_code = static_cast<char>(EntityOperation::CREATE);
    char entity_type;
    char id = static_cast<char>(entity);

    auto music = _registry.get_components<rtype_protocol::Music>()[entity];
    if (music.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*music));
    }
    auto sound = _registry.get_components<rtype_protocol::Sound>()[entity];
    if (sound.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*sound));
    }
    auto sprite = _registry.get_components<rtype_protocol::Sprite>()[entity];
    if (sprite.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*sprite));
    }
    auto bg = _registry.get_components<rtype_protocol::Background>()[entity];
    if (bg.has_value()) {
        this->broadcast(op_code, static_cast<char>(EntityType::MUSIC), _encoder.encode(*bg));
    }
}

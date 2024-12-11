/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Server
*/

#include "Server.hpp"
#include <string>


std::size_t endpoint_hash_class::operator()(const udp::endpoint &ep) const {
    return std::hash<std::string>()(ep.address().to_string() + ":" + std::to_string(ep.port()));
}


Server::Server() 
    : _api()
{
    _api.start_server("5000");
}

Server::~Server() 
{
}

int Server::loop() 
{
    std::string bgname = "./orange.png";
    while (true) {
        if (_api.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = _api.get_data();

            if (_clients.find(data.sender_endpoint) == _clients.end()) {
                _clients.insert(data.sender_endpoint);
                std::cout << "Nouveau client ajouté : " 
                        << data.sender_endpoint.address().to_string()
                        << ":" << data.sender_endpoint.port() << std::endl;

                data.data = std::vector<char>(bgname.begin(), bgname.end());

                data.data.insert(data.data.begin(), static_cast<char>(2));
                data.data.insert(data.data.begin(), static_cast<char>(EntityType::BACKGROUND));
                data.data.insert(data.data.begin(), static_cast<char>(EntityOperation::CREATE));

                _api.reply_to(data);
            }
        }
    }

    return 0;
}

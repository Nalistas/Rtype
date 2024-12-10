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
    : api()
{
    api.start_server("5000");
}

Server::~Server() 
{
}

int Server::loop() 
{
    while (true) {

        if (api.has_data()) {
            rtype_protocol::AsioApi::UDP_DATA data = api.get_data();

            if (clients.find(data.sender_endpoint) == clients.end()) {
                clients.insert(data.sender_endpoint);
                std::cout << "Nouveau client ajouté : " 
                        << data.sender_endpoint.address().to_string()
                        << ":" << data.sender_endpoint.port() << std::endl;
                api.reply_to(data);
            }
        }
        // add client if not exist
    }

    return 0;
}

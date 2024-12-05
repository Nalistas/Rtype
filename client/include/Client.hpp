/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client
*/

#ifndef CLIENT_HPP_
#define CLIENT_HPP_

#include <iostream>
#include <asio.hpp>

using asio::ip::udp;

class Client {
    public:
        Client();
        ~Client();
        void send_message(const std::string &message);
        bool connect(const std::string &port);
        std::string get_data();
        bool has_data();
        void process_message(const std::string &message);
        void create_entity(int entity_type_id, int entity_id, const std::string& entity_data);
        void delete_entity(int entity_id);
        void update_entity(int entity_id, const std::string& updated_data);


    private:
        asio::io_context io_context;
        udp::resolver resolver;
        udp::endpoint endpoint;
        udp::socket socket;
        bool connected;
};

#endif /* !CLIENT_HPP_ */

/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TCPPROTOCOL
*/

#include "registry.hpp"
#include "IGame.hpp"
#include <memory>
#include <map>
#include <functional>

#ifndef TCPPROTOCOL_HPP_
    #define TCPPROTOCOL_HPP_

class TcpProtocol {
    public:
        TcpProtocol(std::map<std::shared_ptr<asio::ip::tcp::socket>, std::string> &clients);
        ~TcpProtocol();

        char setName(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<char> data);
        int interpreter(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<char> data);

    private:
        ecs::registry _registry;
        std::unordered_map<char, std::function<void(std::istringstream&)>> _commandMap;
        std::map<std::shared_ptr<asio::ip::tcp::socket>, std::string> &_clients;

};

#endif /* !TCPPROTOCOL_HPP_ */

/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TCPPROTOCOL
*/

#include "registry.hpp"
#include "IGame.hpp"
#include "TcpServer.hpp"
#include <memory>
#include <map>
#include <functional>

#ifndef TCPPROTOCOL_HPP_
    #define TCPPROTOCOL_HPP_

class TcpProtocol {
    public:
        TcpProtocol(TcpServer &tcpServer);
        ~TcpProtocol();

        int interpreter(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<char> data);

    private:
        ecs::registry _registry;
        std::unordered_map<char, std::function<void(std::shared_ptr<asio::ip::tcp::socket>, std::istringstream&)>> _commandMap;
        TcpServer &_tcpServer;

};

#endif /* !TCPPROTOCOL_HPP_ */

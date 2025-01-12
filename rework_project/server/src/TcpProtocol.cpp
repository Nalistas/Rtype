/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TcpProtocol
*/

#include "TcpProtocol.hpp"
#include <sstream>


TcpProtocol::TcpProtocol(TcpServer &server) : _tcpServer(server)
{
    _commandMap[1] = [this](std::shared_ptr<asio::ip::tcp::socket> client, std::istringstream& params) {
        std::string name;
        params >> name;
        _tcpServer._clients[client] = name;
        std::cout << "Set " << _tcpServer._clients[client] << " name\n";
    };
}

TcpProtocol::~TcpProtocol()
{
}

int TcpProtocol::interpreter(std::shared_ptr<asio::ip::tcp::socket> client, std::vector<char> data)
{
    std::istringstream stream(std::string(data.begin(), data.end()));
    char commandId;
    stream >> commandId;

    if (_commandMap.find(commandId) != _commandMap.end()) {
        _commandMap[commandId](client, stream);
    } else {
        std::cout << "Command not founded\n";
    }
}

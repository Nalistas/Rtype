/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** TcpProtocol
*/

#include "TcpProtocol.hpp"
#include <sstream>


TcpProtocol::TcpProtocol()
{
    _commandMap[1] = [this](std::istringstream& params) {
        std::string name;
        params >> name;
        setName(name);
    };
}

TcpProtocol::~TcpProtocol()
{
}

int TcpProtocol::interpreter(std::string &client, std::vector<char> data)
{
    std::istringstream stream(std::string(data.begin(), data.end()));
    char commandId;
    stream >> commandId;

    if (_commandMap.find(commandId) != _commandMap.end()) {
        _commandMap[commandId](stream);
    } else {
        std::cout << "Commande inconnue\n";
    }
}

char TcpProtocol::setName(std::string &client, std::string name)
{

    std::cout << "New connection from " << name << std::endl;
}

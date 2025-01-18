/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** RoomsCore
*/

#include "RoomsCore.hpp"
#include "TcpProtocol.hpp"
#include <string>
#include <iostream>

RoomsCore::RoomsCore(std::string const &port) :
    _tcpServer("0.0.0.0", port)
{
    setGamesRessources();

    for (auto it : this->_gameList) {
        std::cout << it << std::endl;
    }
}

RoomsCore::~RoomsCore()
{
}

void RoomsCore::checkNewClients(void)
{
    auto client = _tcpServer.accept();

    if (!client) {
        return;
    }

    if (_clients.find(client) == _clients.end()) {
        _clients.insert({client, Client()});
    }
}

void RoomsCore::checkClients(TcpProtocol &tcpProtocol)
{
    CLIENT_DATA_STATE state;
    auto it = _clients.begin();
    
    while (it != _clients.end()) {
        state = _tcpServer.hasDataToRead(it->first);
        if (state == DATA) {
            auto client = it->first;
            treatClient(client, tcpProtocol);
        }
        if (state == DISCONNECTED || state == CLIENT_ERROR) {
            it->first->close();
            it = _clients.erase(it);
            std::cout << "Client disconnected." << std::endl;
            continue;
        }
        if (state == EMPTY) {
            continue;
        }
        ++it;
    }
}

void RoomsCore::treatClient(std::shared_ptr<asio::ip::tcp::socket> &client, TcpProtocol &tcpProtocol)
{
    std::vector<uint8_t> data = _tcpServer.receive(client);

    std::cout << "-------------------------------------------------------------------------" << std::endl;
    std::cout << "Received data from client: " << client << " \"" << this->_clients[client].getName() << "\"" << std::endl;
    std::cout << "Received data (Raw values): " << std::string(data.begin(), data.end()) << std::endl;
    for (uint8_t c : data) {
        std::cout << static_cast<int>(c) << " ";
    }
    std::cout << std::endl << std::endl << "Launching interpreter..." << std::endl;
    tcpProtocol.interpreter(client, data);
}

void RoomsCore::setGameToLaunch(uint8_t roomId)
{
    auto it = _rooms.find(roomId);
    std::vector<uint8_t> data = {TcpProtocol::INSTRUCTIONS_SERVER_TO_CLIENT::START_GAME};

    if (it == _rooms.end()) {
        return;
    }
    this->_roomsToLaunch.emplace(*it);
    this->_rooms.erase(roomId);

    auto clientIt = this->_clients.begin();
    while (clientIt != this->_clients.end()) {
        if (clientIt->second.getRoomId() == roomId) {
            _tcpServer.send(clientIt->first, data);
            this->_clientsToLaunch.emplace(*clientIt);
            clientIt = this->_clients.erase(clientIt);
        } else {
            ++clientIt;
        }
    }
}

int RoomsCore::find_available_port(unsigned short start_port)
{
    asio::io_context io_context;

    for (unsigned short port = start_port; port <= 65535; ++port) {
        try {
            asio::ip::tcp::acceptor acceptor(io_context, 
                asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));
            return port;
        } catch (const std::exception &e) {
            continue;
        }
    }
}

void RoomsCore::launchGame()
{
    process::Process my_process;
    for (auto &room : this->_roomsToLaunch) {
        auto game = room.second.getGameName();
        if (std::find(this->_gameList.begin(), this->_gameList.end(), game) == this->_gameList.end()) {
            std::cerr << "Game not found" << std::endl;
            continue;
        }
        int port = find_available_port(1024);
        std::string game_path = this->_gameNameToPath[game];

        #ifdef _WIN32
            std::vector<std::string> vec = {"./build/r-type_server.exe", "-udp", std::to_string(port), game_path};
            my_process.execProcess(vec);
            sendGameRessourcesToTheRoom(port, game, room.second);
        #else
            std::vector<std::string> vec = {"./build/r-type_server", "-udp", std::to_string(port), game_path};
            my_process.execProcess(vec);
            sendGameRessourcesToTheRoom(port, game, room.second);
        #endif
    }
}

void RoomsCore::sendGameRessourcesToTheRoom(int port, std::string game, Room room)
{
    // auto it = this->_ressources.find(game);
    // auto ressources = it->second.getRessourcess();

    // for (auto &client : this->_clientsToLaunch) {
    //     for (auto &ressource : ressources) {
    //         _tcpServer.send(client.first, ressource);
    //     }
    // }
}

std::vector<Client> RoomsCore::getClients()
{
    std::vector<Client> clients;

    for (auto &client : this->_clientsToLaunch) {
        clients.emplace_back(client.second);
    }
    return clients;
}

void RoomsCore::run(void)
{
    std::function<void(uint8_t roomId)> launchGame = [this](uint8_t roomId) { this->setGameToLaunch(roomId); };
    TcpProtocol tcp_protocol(_rooms, _clients, _tcpServer, launchGame, _gameList);

    while (true) {
        checkNewClients();
        checkClients(tcp_protocol);
    }
}

void RoomsCore::setGamesRessources(void)
{
    SafeDirectoryLister lister(".", true);
    std::list<std::string> files;

    while (lister.isGood()) {
        std::string file_name = lister.get();

        #ifdef _WIN32
        if (file_name.find(".dll") != std::string::npos)
        #else
        if (file_name.find(".so") != std::string::npos)
        #endif
        {
            std::cout << "Found game: " << file_name << std::endl;
            files.emplace_back("./" + file_name);
        }
    }

    if (files.size() == 0) {
        throw std::runtime_error("No game found");
    }

    for (const auto &file : files) {
        try {
            DLLdr::DLLoader<rtype::IGame> game_loader;
            game_loader.open(file);
            auto game_ptr = game_loader.getSym("entry_point");
            this->_ressources.emplace(game_ptr->getName(), game_ptr);
            this->_gameList.emplace_back(game_ptr->getName());
            this->_gameNameToPath.emplace(game_ptr->getName(), file);
        } catch (const std::exception &e) {
            std::cerr << "Error while loading game: " << file << std::endl;
            std::cerr << "Exception: " << e.what() << std::endl;
        } catch (...) {
            std::cerr << "Unknown error occurred while loading game: " << file << std::endl;
        }
    }

}

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
#include <chrono>
#include <thread>

RoomsCore::RoomsCore(std::string const &executable_name, std::string const &port, bool &running) :
    _tcpServer("0.0.0.0", port), _rooms(), _clients(), _gameList(), _executable_name(executable_name), _run(running)
{
    setGamesRessources();

    for (auto it : this->_gameList) {
        std::cout << it << std::endl;
    }
}

RoomsCore::~RoomsCore()
{
}

void RoomsCore::stop(void)
{
    _run = false;
}

void RoomsCore::run(void)
{
    std::function<void(uint8_t roomId)> launchGame = [this](uint8_t roomId) { this->setGameToLaunch(roomId); };
    TcpProtocol tcp_protocol(_rooms, _clients, _tcpServer, launchGame, _gameList);

    while (_run) {
        checkNewClients();
        checkClients(tcp_protocol);
        this->launchGame();
        std::this_thread::sleep_for(std::chrono::milliseconds(30));
    }
}

void RoomsCore::checkNewClients(void)
{
    auto client = _tcpServer.accept();

    if (!client) {
        return;
    }
    std::cout << "New client connected." << std::endl;

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
        ++it;
    }
}

void RoomsCore::treatClient(std::shared_ptr<asio::ip::tcp::socket> &client, TcpProtocol &tcpProtocol)
{
    std::vector<uint8_t> data = _tcpServer.receive(client);

    // std::cout << "-------------------------------------------------------------------------" << std::endl;
    // std::cout << "Received data from client: " << client << " \"" << this->_clients[client].getName() << "\"" << std::endl;
    // std::cout << "Received data (Raw values): " << std::string(data.begin(), data.end()) << std::endl;
    // for (uint8_t c : data) {
    //     std::cout << static_cast<int>(c) << " ";
    // }
    std::cout << std::endl << std::endl << "Launching interpreter..." << std::endl;
    tcpProtocol.interpreter(client, data);
}

void RoomsCore::setGameToLaunch(uint8_t roomId)
{
    auto it = _rooms.find(roomId);
    // std::vector<uint8_t> data = {TcpProtocol::INSTRUCTIONS_SERVER_TO_CLIENT::START_GAME};

    if (it == _rooms.end()) {
        return;
    }
    this->_roomsToLaunch.emplace(*it);
    this->_rooms.erase(roomId);

    auto clientIt = this->_clients.begin();
    while (clientIt != this->_clients.end()) {
        if (clientIt->second.getRoomId() == roomId) {
            // _tcpServer.send(clientIt->first, data);
            this->_clientsToLaunch.emplace(*clientIt);
        }
        ++clientIt;
    }
}

int RoomsCore::find_available_port(unsigned short start_port)
{
    asio::io_context io_context;

    for (unsigned short port = start_port; port != 0; ++port) {
        try {
            asio::ip::tcp::acceptor acceptor(io_context, 
                asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port));

            asio::ip::udp::socket udp_socket(io_context, 
                asio::ip::udp::endpoint(asio::ip::udp::v4(), port));
            return port;
        } catch (const std::exception &e) {
            continue;
        }
    }
    return -1;
}

void RoomsCore::launchGame()
{
    if (this->_clientsToLaunch.empty() && this->_roomsToLaunch.empty())
        return;
    for (auto &client : this->_clientsToLaunch) {
        this->_clients.erase(client.first);
    }
    for (auto &room : this->_roomsToLaunch) {
        this->_rooms.erase(room.first);
    }
    std::vector<uint8_t> ip = get_local_ip();


    for (auto &room : this->_roomsToLaunch) {
        auto game = room.second.getGameName();
        if (std::find(this->_gameList.begin(), this->_gameList.end(), game) == this->_gameList.end()) {
            std::cerr << "Game not found" << std::endl;
            continue;
        }
        int port = find_available_port(2000);
        std::string game_path = this->_gameNameToPath[game];
        std::vector<std::string> vec = {_executable_name, "-udp", std::to_string(port), game_path};
        _my_process.execProcess(vec);
        std::cout << "Game launched" << std::endl;


        sendGameRessourcesToTheRoom(game, room.first);
        std::vector<uint8_t> data(8);

        data[0] = static_cast<uint8_t>(TcpProtocol::INSTRUCTIONS_SERVER_TO_CLIENT::START_GAME);
        data[1] = static_cast<uint8_t>(ip[0]);
        data[2] = static_cast<uint8_t>(ip[1]);
        data[3] = static_cast<uint8_t>(ip[2]);
        data[4] = static_cast<uint8_t>(ip[3]);
        data[5] = static_cast<uint8_t>(port / 100);
        data[6] = static_cast<uint8_t>(port % 100);
        data[7] = static_cast<uint8_t>(room.first);

        for (auto &client : this->_clientsToLaunch) {
            if (client.second.getRoomId() != room.first)
                continue;
            // int client_id = getClientId(room.first, client.first);
            _tcpServer.send(client.first, data);
        }
    }
    for (auto &client : this->_clientsToLaunch) {
        client.second.setRoomId(0);
        _clients.emplace(client.first, client.second);
    }
    _clientsToLaunch.clear();
    _roomsToLaunch.clear();
}

int RoomsCore::getClientId(const uint8_t room, const std::shared_ptr<asio::ip::tcp::socket> &clientt)
{
    int id = 0;
    std::list<std::pair<std::shared_ptr<asio::ip::tcp::socket>, Client>> clients = this->getClients(room);
    for (auto &client : clients) {
        if (clientt == client.first)
            return id;
        id++;
    }
    return id;
}

void RoomsCore::sendGameRessourcesToTheRoom(std::string game, const uint8_t  room)
{
    auto ressources = this->_ressources.find(game)->second.getRessourcess();
    for (auto &ressource : ressources) {
        for (auto &c : ressource) {
            std::cout << static_cast<int>(c) << " ";
        }
        std::cout << std::endl;
    }
    for (auto &client: this->_clientsToLaunch) {
        if (client.second.getRoomId() != room)
            continue;
        for (auto &ressource : ressources) {
            _tcpServer.send(client.first, ressource);
        }
    }
}

std::list<std::pair<std::shared_ptr<asio::ip::tcp::socket>, Client>> RoomsCore::getClients(const uint8_t room)
{
    std::list<std::pair<std::shared_ptr<asio::ip::tcp::socket>, Client>> clients;

    for (auto &client : this->_clients) {
        if (client.second.getRoomId() == room) {
            clients.emplace_back(client.first, client.second);
        }
    }
    return clients;
}

std::vector<uint8_t> RoomsCore::get_local_ip() 
{
    try {
        asio::io_context io_context;

        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::query query(asio::ip::host_name(), "");
        auto endpoints = resolver.resolve(query);

        for (const auto& endpoint : endpoints) {
            if (endpoint.endpoint().address().is_v4()) {
                auto ip = endpoint.endpoint().address().to_string();
                std::vector<uint8_t> transformed_ip(4);
                size_t pos = 0;
                size_t prev_pos = 0;
                std::size_t count = 0;
                while ((pos = ip.find('.', prev_pos)) != std::string::npos) {
                    int segment = std::stoi(ip.substr(prev_pos, pos - prev_pos));
                    transformed_ip[count]= static_cast<uint8_t>(segment);
                    prev_pos = pos + 1;
                    count++;
                }
                transformed_ip[count]= static_cast<uint8_t>(std::stoi(ip.substr(prev_pos)));       
                return transformed_ip;
            }
        }
        throw std::runtime_error("No IPv4 adress founded.");

    } catch (const std::exception& e) {
        std::cerr << "Error : " << e.what() << std::endl;
        throw;
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
    for (auto ressource : this->_ressources) {
        std::cout << ressource.first << std::endl;
        for (auto lst : ressource.second.getRessourcess()) {
            for (auto c : lst) {
                std::cout << static_cast<int>(c) << " ";
            }
            std::cout << std::endl;
        }
    }
}

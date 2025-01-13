/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** Room
*/


#ifndef ROOM_HPP_
    #define ROOM_HPP_

    #include <vector>
    #include <memory>
    #include <asio.hpp>

// scanner le jeu pour savoir combien de joueurs peuvent y jouer en meme temps ?
// mettre un max de joueur dans la room ?

class Room {
    public:
        Room(std::string name, std::string gameName, int id);
        ~Room();
        void addClient(std::shared_ptr<asio::ip::tcp::socket> client);
        void removeClient(std::shared_ptr<asio::ip::tcp::socket> client);
        void changeClientStatus(std::shared_ptr<asio::ip::tcp::socket> client);
        std::vector<std::pair<std::shared_ptr<asio::ip::tcp::socket>, bool>> getClients();
        std::string getName();
        std::string getGameName();
        int getId();
        void setName(std::string const &name);
        bool isEveryoneReady();
        int getNbClients();
        bool isClientInRoom(std::shared_ptr<asio::ip::tcp::socket> client);


    private:
        std::vector<std::pair<std::shared_ptr<asio::ip::tcp::socket>, bool>> _clients;
        std::string _name;
        std::string _gameName;
        int _id;

};

#endif /* !ROOM_HPP_ */

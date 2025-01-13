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
        Room(std::string const &name, std::string const &gameName, std::shared_ptr<asio::ip::tcp::socket> &owner);
        ~Room();

        std::shared_ptr<asio::ip::tcp::socket> const &getOwner() const;
        std::string const &getName() const;
        std::string const &getGameName() const;

        void setName(std::string const &name);
        void setGameName(std::string const &gameName);
        void setOwner(std::shared_ptr<asio::ip::tcp::socket> &owner);

    private:
        std::string _name;
        std::string _gameName;
        std::shared_ptr<asio::ip::tcp::socket> _owner;

};

#endif /* !ROOM_HPP_ */

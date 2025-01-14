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
        /**
         * @brief Construct a new Room object
         * 
         * @param name the name of the room
         * @param gameName the name of the game
         * @param owner the owner of the room (the socket of the client)
         */
        Room(std::string const &name, std::string const &gameName, std::shared_ptr<asio::ip::tcp::socket> &owner);

        /**
         * @brief Destroy the Room object
         */
        ~Room();

        /**
         * @brief Get the owner of the room
         * 
         * @return std::shared_ptr<asio::ip::tcp::socket> const& which is the socket of the owner
         */
        std::shared_ptr<asio::ip::tcp::socket> const &getOwner() const;

        /**
         * @brief Get the name of the room
         * 
         * @return std::string const& which is the name of the room
         */
        std::string const &getName() const;

        /**
         * @brief Get the game name of the room
         * 
         * @return std::string const& which is the name of the game
         */
        std::string const &getGameName() const;

        /**
         * @brief Set the name of the room
         * 
         * @param name the name of the room
         */
        void setName(std::string const &name);

        /**
         * @brief Set the game name of the room
         * 
         * @param gameName the name of the game
         */
        void setGameName(std::string const &gameName);

        /**
         * @brief Set the owner of the room
         *
         * @param owner the owner of the room (the socket of the client)
         */
        void setOwner(std::shared_ptr<asio::ip::tcp::socket> &owner);

    private:
        std::string _name;
        std::string _gameName;
        std::shared_ptr<asio::ip::tcp::socket> _owner;

};

#endif /* !ROOM_HPP_ */

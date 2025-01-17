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


class ClientRoom {
    public:
        /**
         * @brief Construct a new ClientRoom object
         * 
         * @param name the name of the ClientRoom
         * @param gameName the name of the game
         * @param owner the owner of the ClientRoom (the socket of the client)
         */
        ClientRoom(std::string const &name, int id, int nbPlayers);

        /**
         * @brief Destroy the ClientRoom object
         */
        ~ClientRoom();

        /**
         * @brief Get the name of the ClientRoom
         * 
         * @return std::string const & the name of the ClientRoom
         */
        std::string const &getName() const;

        /**
         * @brief Get theid of the ClientRoom
         * 
         * @return int the id of the ClientRoom
         */
        int getId() const;

        /**
         * @brief Get the number of players in the ClientRoom
         * 
         * @return int the number of players in the ClientRoom
         */
        int getNbPlayers() const;

        /**
         * @brief Set the number of players in the ClientRoom
         * 
         * @param nbPlayers the number of players in the ClientRoom
         */
        void setNbPlayers(int nbPlayers);


    private:
        std::string _name;
        int _id;
        int _nbPlayers;

};

#endif /* !ClientRoom_HPP_ */

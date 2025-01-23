/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** RessourcesManager
*/

#include "IGame.hpp"
#include <memory>
#include <list>
#include <vector>

#ifndef RESSOURCESMANAGER_HPP_
    #define RESSOURCESMANAGER_HPP_

/**
 * @brief Class to manage the ressources of a game
 * This class is used to get all the ressources of a game
 * It takes a std::unique_ptr<rtype::IGame> as parameter
 * It will get all the backgrounds, sprites, musics and client actions of the game
 * It will then transform them into a vector of bytes that can be sent to the clients
 * The vector of bytes will be stored in the _ressources member
 * The getRessourcess method can then be used to get the vector of bytes
 */
class RessourcesManager {
    public:

        /**
         * @brief Construct a new Ressources Manager object
         */
        // RessourcesManager() = default;

        /**
         * @brief Construct a new Ressources Manager object
         * @param game the game for which we want to get the ressources
         */
        RessourcesManager(std::unique_ptr<rtype::IGame> &game);

        /**
         * @brief Destroy the Ressources Manager object
         */
        ~RessourcesManager();

        /**
         * @brief Get the Ressourcess object
         */
        std::list<std::vector<uint8_t>> &getRessourcess();

        /**
         * @brief Get the Game Name object
         */
        std::string const &getGameName() const;

    private:
        std::list<std::vector<uint8_t>> _ressources;
        std::string _game_name;

        /**
         * @brief Transform a background into a vector of bytes
         * @param background the background to transform
         * @param id the id of the background
         * @return std::vector<uint8_t> the vector of bytes
         */
        std::vector<uint8_t> transformBackground(rtype::Background const &background, uint32_t id);

        /**
         * @brief Transform a sprite into a vector of bytes
         * @param sprite the sprite to transform
         * @param id the id of the sprite
         * @return std::vector<uint8_t> the vector of bytes
         */
        std::vector<uint8_t> transformSprite(rtype::Sprite const &sprite, uint32_t id);

        /**
         * @brief Transform a music into a vector of bytes
         * @param music the music to transform
         * @param id the id of the music
         * @return std::vector<uint8_t> the vector of bytes
         */
        std::vector<uint8_t> transformMusic(std::string const &music, uint32_t id);

        /**
         * @brief Transform a client action into a vector of bytes
         * @param action the action to transform
         * @param id the id of the action
         * @return std::vector<uint8_t> the vector of bytes
         */
        std::vector<uint8_t> transformAction(rtype::ClientAction const &action, uint32_t id);

        /**
         * @brief Copy a 32-bit unsigned integer into a vector of bytes
         * @param vec the vector of bytes
         * @param pos the position in the vector to copy the integer
         * @param value the integer to copy
         */
        void copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value);
};

#endif /* !RESSOURCESMANAGER_HPP_ */

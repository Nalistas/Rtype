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

class RessourcesManager {
    public:
        RessourcesManager(std::unique_ptr<rtype::IGame> &game);
        ~RessourcesManager();

        std::list<std::vector<uint8_t>> &getRessourcess();

    private:
        std::list<std::vector<uint8_t>> _ressources;

        std::vector<uint8_t> transformBackground(rtype::Background const &background, uint32_t id);
        std::vector<uint8_t> transformSprite(rtype::Sprite const &sprite, uint32_t id);
        std::vector<uint8_t> transformMusic(std::string const &music, uint32_t id);
        std::vector<uint8_t> transformAction(rtype::ClientAction const &action, uint32_t id);
        void copyUint32(std::vector<uint8_t> &vec, std::size_t pos, uint32_t value);
};

#endif /* !RESSOURCESMANAGER_HPP_ */

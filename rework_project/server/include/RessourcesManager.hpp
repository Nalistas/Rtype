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
        RessourcesManager(std::shared_ptr<rtype::IGame> &game);
        ~RessourcesManager();

        std::list<std::vector<char>> &getRessourcess();

    private:
        std::list<std::vector<char>> _ressources;

        std::vector<char> transformBackground(rtype::Background const &background, uint32_t id);
        std::vector<char> transformSprite(rtype::Sprite const &sprite, uint32_t id);
        std::vector<char> transformMusic(std::string const &music, uint32_t id);

        void copyUint32(std::vector<char> &vec, std::size_t pos, uint32_t value);
};

#endif /* !RESSOURCESMANAGER_HPP_ */

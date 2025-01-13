/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** GameLauncher
*/

#include <string>
#include <list>
#include <vector>

#include "DLLoader.hpp"
#include "IGame.hpp"

#ifndef GAMELAUNCHER_HPP_
    #define GAMELAUNCHER_HPP_

class GameLauncher {
    public:
        GameLauncher(std::string const &game_path);
        ~GameLauncher();

        std::list<std::vector<uint8_t>> getRessources();

        std::string const &getIp();

        std::string const &getPort();

        void launch();


    private:
        std::unique_ptr<rtype::IGame> _game;
        DLLdr::DLLoader<rtype::IGame> _loader;
};

#endif /* !GAMELAUNCHER_HPP_ */

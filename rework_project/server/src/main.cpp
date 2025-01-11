/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** main
*/

#include <iostream>
#include "RoomsCore.hpp"
#include "registry.hpp"
#include "isystem.hpp"
#include "GameLauncher.hpp"


int main()
{
    GameLauncher launcher("./libr-type.so");
    std::list<GameLauncher::Player> players = {{"player1", "127.0.0.1"}, {"player2", "127.0.0.1"}, {"player3", "127.0.0.1"}};
    launcher.launch(players);

    // RoomsCore core("12345");
    // core.run();
    return 0;
}

/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** Game
*/

#include <unordered_map>
#include <map>
#include <array>
#include <cstdint>
#include "Sprite.hpp"
#include "RayMusic.hpp"
#include "Background.hpp"
#include "UdpClient.hpp"
#include "Window.hpp"
#include "GraphicsManager.hpp"

#ifndef GAME_HPP_
    #define GAME_HPP_

class Game {
    public:
        Game(
            std::array<std::map<uint32_t, uint32_t>, 2> actions,
            std::map<uint32_t, raylib::Sprite> &sprites,
            std::map<uint32_t, Background> &backgrounds,
            std::map<uint32_t, raylib::RayMusic> &musics,
            UdpClient &_client,
            raylib::Window &_win
        );
        ~Game();

        void run(void);

        void interpretor(void);

        void moveSprites(void);


    private:
        std::array<std::map<uint32_t, uint32_t>, 2> _actions;
        std::map<uint32_t, raylib::Sprite> &_sprites;
        std::map<uint32_t, std::pair<int, int>> _spritesSpeed;
        std::map<uint32_t, Background> &_backgrounds;
        std::map<uint32_t, raylib::RayMusic> &_musics;
        UdpClient &_client;
        raylib::Window &_win;

        GraphicsManager _graphics;

        std::unordered_map<uint32_t, uint64_t> _entitiesSprites;
        std::unordered_map<uint8_t, std::function<void(std::vector<uint8_t>&)>> _commandMap;
};

#endif /* !GAME_HPP_ */

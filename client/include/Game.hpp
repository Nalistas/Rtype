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

/**
 * @brief Game class to handle the game
 */
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

        /**
         * @brief Run the game
         */
        void run(void);

        /**
         * @brief Interpret the actions
         */
        void interpretor(void);

        /**
         * @brief Move the sprites
         */
        void moveSprites(void);

    private:
        /**
         * 
         */
        void sendAction(raylib::Vector2 pos, uint32_t id);

        /**
         * 
         */
        uint32_t invert(uint32_t value);


        /**
         * 
         */
        void processBackground(std::vector<uint8_t> &data);

        /**
         * 
         */
        void processCreateEntity(std::vector<uint8_t> &data);

        /**
         * 
         */
        void processDeleteEntity(std::vector<uint8_t> &data);

        /**
         * 
         */
        void processUpdateSpeed(std::vector<uint8_t> &data);

        /**
         * 
         */
        void processUpdatePosition(std::vector<uint8_t> &data);

        /**
         * 
         */
        void playMusic(std::vector<uint8_t> &data);

        /**
         * 
         */
        void processText(std::vector<uint8_t> &data);


    private:
        std::array<std::map<uint32_t, uint32_t>, 2> _actions;
        std::map<uint32_t, raylib::Sprite> &_sprites;
        std::map<uint32_t, std::pair<char, char>> _spritesSpeed;
        std::map<uint32_t, Background> &_backgrounds;
        std::map<uint32_t, raylib::RayMusic> &_musics;
        UdpClient &_client;
        raylib::Window &_win;

        GraphicsManager _graphics;

        int64_t _ms_last_update;

        std::unordered_map<uint32_t, uint64_t> _entitiesSprites;
        std::unordered_map<uint8_t, std::function<void(std::vector<uint8_t>&)>> _commandMap;
        std::unordered_map<uint8_t, uint64_t> _entitiesText;
};

#endif /* !GAME_HPP_ */

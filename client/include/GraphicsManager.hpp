/*
** EPITECH PROJECT, 2025
** rtype
** File description:
** GraphicsManager
*/

#include "Window.hpp"
#include "Sprite.hpp"
#include "RayMusic.hpp"
#include "RayText.hpp"
#include "Background.hpp"
#include <unordered_map>
#include <chrono>

#ifndef GRAPHICSMANAGER_HPP_
    #define GRAPHICSMANAGER_HPP_

/**
 * @brief GraphicsManager class to handle the graphics part of the client
 */
class GraphicsManager {
    public:
        GraphicsManager(raylib::Window &window);
        ~GraphicsManager();

        void display();

        void changeScene(std::function<void()> const &callback);

        uint64_t addSprite(raylib::Sprite const &sprite);
        uint64_t addMusic(raylib::RayMusic const &music);
        uint64_t addText(raylib::RayText const &text);
        uint64_t addBackground(Background const &background);

        void removeSprite(uint64_t id);
        void removeMusic(uint64_t id);
        void removeText(uint64_t id);
        void removeBackground(uint64_t id);

        raylib::Sprite &getSprite(uint64_t id);
        raylib::RayMusic &getMusic(uint64_t id);
        raylib::RayText &getText(uint64_t id);
        Background &getBackground(uint64_t id);

        void onSpriteClick(uint64_t id, std::function<void()> callback);
        void onTextClick(uint64_t id, std::function<void()> callback);

        void bindTextToKeyboard(uint64_t id);
        void removeKeyboardBinding(void);
        uint64_t getTextIdBinded(void);


        void addKeyBinding(uint32_t key, bool pressed, std::function<void()> callback);
        void removeKeyBinding(uint32_t key, bool pressed);

    private:
        void _clearElements(void);
        bool _mustClear = false;
        std::function<void()> next_scene;

        raylib::Window &_window;

        bool _is_keyboard_binded_to_text = false;
        uint64_t _keyboard_bound_id = 0;

        std::chrono::time_point<std::chrono::high_resolution_clock> _last_frame_time;

        std::unordered_map<uint64_t, raylib::Sprite> _sprites;
        std::unordered_map<uint64_t, raylib::RayMusic> _musics;
        std::unordered_map<uint64_t, raylib::RayText> _texts;
        std::unordered_map<uint64_t, Background> _backgrounds;

        std::unordered_map<uint64_t, std::function<void()>> _spriteClickCallbacks;
        std::unordered_map<uint64_t, std::function<void()>> _textClickCallbacks;
        std::unordered_map<uint32_t, std::function<void()>> _keyBindingsPressed;
        std::unordered_map<uint32_t, std::function<void()>> _keyBindingsReleased;
};

#endif /* !GRAPHICSMANAGER_HPP_ */

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

        /**
         * @brief Display the window
         */
        void display();

        /**
         * @brief Cchange the scene of the window
         * 
         * @param callback the callback to call when the scene is changed
         */
        void changeScene(std::function<void()> const &callback);

        /**
         * @brief Add a sprite to the window
         * 
         * @param sprite the sprite to add
         * @return the id of the sprite
         */
        uint64_t addSprite(raylib::Sprite const &sprite);

        /**
         * @brief Add a music to the window
         * 
         * @param music the music to add
         * @return the id of the music
         */
        uint64_t addMusic(raylib::RayMusic const &music);

        /**
         * @brief Add a text to the window
         * 
         * @param text the text to add
         * @return the id of the text
         */
        uint64_t addText(raylib::RayText const &text);

        /**
         * @brief Add a background to the window
         * 
         * @param background the background to add
         * @return the id of the background
         */
        uint64_t addBackground(Background const &background);

        /**
         * @brief Remove a sprite from the window
         * 
         * @param id the id of the sprite to remove
         */
        void removeSprite(uint64_t id);

        /**
         * @brief Remove a music from the window
         * 
         * @param id the id of the music to remove
         */
        void removeMusic(uint64_t id);

        /**
         * @brief Remove a text from the window
         * 
         * @param id the id of the text to remove
         */
        void removeText(uint64_t id);

        /**
         * @brief Remove a background from the window
         * 
         * @param id the id of the background to remove
         */
        void removeBackground(uint64_t id);

        /**
         * @brief Get a sprite from the window
         * 
         * @param id the id of the sprite to get
         * @return the sprite
         */
        raylib::Sprite &getSprite(uint64_t id);

        /**
         * @brief Get a music from the window
         * 
         * @param id the id of the music to get
         * @return the music
         */
        raylib::RayMusic &getMusic(uint64_t id);

        /**
         * @brief Get a text from the window
         * 
         * @param id the id of the text to get
         * @return the text
         */
        raylib::RayText &getText(uint64_t id);

        /**
         * @brief Get a background from the window
         * 
         * @param id the id of the background to get
         * @return the background
         */
        Background &getBackground(uint64_t id);

        /**
         * @brief check if a sprite is clicked on
         * 
         * @param id the id of the sprite
         * @param callback the callback to call when the sprite is clicked
         */
        void onSpriteClick(uint64_t id, std::function<void()> callback);

        /**
         * @brief check if a text is clicked on
         * 
         * @param id the id of the text
         * @param callback the callback to call when the text is clicked
         */
        void onTextClick(uint64_t id, std::function<void()> callback);

        /**
         * @brief bind the keyboard to a text
         * 
         * @param id the id of the text
         */
        void bindTextToKeyboard(uint64_t id);

        /**
         * @brief remove the keyboard binding
         */
        void removeKeyboardBinding(void);

        /**
         * @brief Get the id of the text binded to the keyboard
         * 
         * @return the id of the text binded to the keyboard
         */
        uint64_t getTextIdBinded(void);

        /**
         * @brief Get the text binded to the keyboard
         * 
         * @return the text binded to the keyboard
         */
        void addKeyBinding(uint32_t key, bool pressed, std::function<void()> callback);

        /**
         * @brief Remove a key binding
         * 
         * @param key the key to remove
         * @param pressed the state of the key to remove
         */
        void removeKeyBinding(uint32_t key, bool pressed);

    private:

        /**
         * @brief Clear the elements of the window
         */
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

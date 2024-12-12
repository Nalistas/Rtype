/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** graphics
*/

#include <string>
#include <vector>

#ifndef PROTOCOL_HPP_
    #define PROTOCOL_HPP_

namespace rtype_protocol {

    enum BackgroundDirection {
        X = 1,
        Y = 2
    };

    enum BackgroundMoveType {
        NONE = 0,
        MOVE = 2,
        PARALLAX = 3
    };

    struct Background {
        char speed;
        BackgroundDirection direction;
        bool resize;
        bool repeat;
        std::string path;
    };

    struct Sprite {
        char speed_x;
        char speed_y;
        int pos_x;
        int pos_y;
        int size_x;
        int size_y;
        int text_rect_width;
        int text_rect_height;
        int offset_x;
        int offset_y;
        char nb_frames;
        int ms_per_frame;
        int auto_destroy;
        std::string path;
    };


    struct Music {
        std::string path;
    };

    struct Sound {
        std::string path;
    };

    enum KeyState {
        RELEASED = 0,
        PRESSED = 1
    };

    struct ActionDefinition {
        int key;
        KeyState state;
        bool mouse_pos;
        int id_action;
    };


    class Encoder {
        public: 
            Encoder() noexcept = default;
            ~Encoder() noexcept = default;

            std::vector<char> encode(Background const &background);
            std::vector<char> encode(Sprite const &sprite);
            std::vector<char> encode(Music const &music);
            std::vector<char> encode(Sound const &sound);

            Background decodeBackground(std::vector<char> const &data);
            Sprite decodeSprite(std::vector<char> const &data);
            Music decodeMusic(std::vector<char> const &data);
            Sound decodeSound(std::vector<char> const &data);

    };
}

#endif /* !PROTOCOL_HPP_ */

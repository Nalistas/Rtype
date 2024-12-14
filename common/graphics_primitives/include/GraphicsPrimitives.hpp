/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GraphicsPrimitives
*/

#ifndef GRAPHICSPRIMITIVES_HPP_
    #define GRAPHICSPRIMITIVES_HPP_

#include "GraphicsInterface.hpp"

namespace graphics_interface {

    enum BackgroundDirection {
        X = 1,
        Y = 2
    };

    enum BackgroundMoveType {
        NONE = 0,
        MOVE = 2,
        PARALLAX = 3
    };

    class Background : public IGraphicsInterface {
        public:
            Background() = default;
            ~Background() = default;

            std::vector<char> encode(void) override;
            void decode(std::vector<char> const &) override;


            char speed;
            BackgroundDirection direction;
            bool resize;
            bool repeat;
            std::string path;
    };

    class Sprite : public IGraphicsInterface {
        public:
            Sprite() = default;
            ~Sprite() = default;

            std::vector<char> encode(void) override;
            void decode(std::vector<char> const &) override;

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


    struct Music : public IGraphicsInterface {
        public:
            Music() = default;
            ~Music() = default;

            std::vector<char> encode(void) override;
            void decode(std::vector<char> const &) override;

            std::string path;
    };

    struct Sound : public IGraphicsInterface {
        public:
            Sound() = default;
            ~Sound() = default;

            std::vector<char> encode(void) override;
            void decode(std::vector<char> const &) override;

            std::string path;

    };

    enum KeyState {
        RELEASED = 0,
        PRESSED = 1
    };

    class ActionDefinition : public IGraphicsInterface {

        public:
            ActionDefinition() = default;
            ~ActionDefinition() = default;

            std::vector<char> encode(void) override;
            void decode(std::vector<char> const &) override;

            int key;
            KeyState state;
            bool mouse_pos;
            int id_action;
    };
}

#endif /* !GRAPHICSPRIMITIVES_HPP_ */

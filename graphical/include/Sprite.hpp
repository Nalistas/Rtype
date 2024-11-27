/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Sprite
*/

#include "raylib.h"
#include <string>

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

namespace raylib {

class Sprite {
    public:
        Sprite(std::string const &texture_path);
        Sprite(std::string const &texture_path, Rectangle texture_rect, Rectangle on_window_rect);
        ~Sprite();

        void draw();

        /**
         * @brief Set the texture
         * @param texture_path the path to the texture
         */
        void set_texture(std::string const &texture_path);

        /**
         * @brief Set the texture rect
         * @param texture_rect the texture rect {x, y, width, height}
         */
        void set_source_rect(Rectangle texture_rect);

        /**
         * @brief Set the on window rect
         * @param on_window_rect the on window rect {x, y, width, height}
         */
        void set_destination_rect(Rectangle on_window_rect);

        /**
         * @brief Set the position
         * @param x the x position
         * @param y the y position
         */
        void set_position(float x, float y);

        /**
         * @brief Set the size
         * @param x the x size
         * @param y the y size
         */
        void set_size(float x, float y);

        /**
         * @brief Set the rotation
         * @param rotation the rotation
         */
        void set_rotation(float rotation);

        /**
         * @brief Get the size
         * @return the size as a Vector2 from raylib
         */
        Vector2 get_size() const;

        /**
         * @brief Get the position
         * @return the position as a Vector2 from raylib
         */
        Vector2 get_position() const;

        /**
         * @brief Get the rotation
         * @return the rotation angle
         */
        float get_rotation() const;

    private:
        /// @name the basics attributes
        /// @{

        /// @brief The rectangle on the window where the sprite is drawn
        Rectangle _destination_rect;

        /// @brief The center of the rectangle
        Vector2 _center;

        /// @brief The texture
        Texture2D _texture;

        /// @brief The rotation
        float _rotation;

        /// @}

        /// @name the advanced attributes, for animation, etc
        /// @{

        /// @brief The source rectangle, what part of the texture to draw
        Rectangle _source_rect;

        /// @brief the original origin of the rect of the Frame 1
        Rectangle _source_rect_origin;

        /// @brief The number of state in the animation
        unsigned int _frame_count;

        /// @brief The current frame of the animation
        unsigned int _current_frame;

        /// @brief The offset of the source rect to get the next frame of the animation
        Vector2 _offset;

        /// @}

};

}

#endif /* !SPRITE_HPP_ */

/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** Sprite
*/

#include "Texture.hpp"
#include <string>
#include <memory>

#ifndef SPRITE_HPP_
    #define SPRITE_HPP_

namespace raylib {
    #include "raylib.h"

class Sprite {
    public:
        Sprite();
        Sprite(std::shared_ptr<raylib::TextureCpp> &text);
        Sprite(std::shared_ptr<raylib::TextureCpp> &text, Rectangle texture_rect, Rectangle on_window_rect);
        ~Sprite();

        void draw();

        /**
         * @brief Set the component
         * @param sprite the sprite component
         */

        /**
         * @brief Set the texture
         * @param texture_path the path to the texture
         */
        void set_texture(std::shared_ptr<raylib::TextureCpp> &text);

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

        /**
         * @brief Resize the sprite on the x axis, but modify the y axis to keep the same ratio
         * @param x the new x size
         */
        void resize_x(float x, bool keep_ratio = false);

        /**
         * @brief Resize the sprite on the y axis, but modify the x axis to keep the same ratio
         * @param y the new y size
         */
        void resize_y(float y, bool keep_ratio = false);

        /**
         * @brief Set the offset of the source rect to get the next frame of the animation
         * @param x the x offset
         * @param y the y offset
         */
        void set_offset(float x, float y);

    private:
        /// @name the basics attributes
        /// @{

        /// @brief The rectangle on the window where the sprite is drawn
        Rectangle _destination_rect;

        /// @brief The center of the rectangle
        Vector2 _center;

        /// @brief The texture
        std::shared_ptr<TextureCpp> _texture;

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

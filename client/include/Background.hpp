/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** Background
*/

#include "Raylib/Sprite.hpp"

#include <ctime>
#include <functional>

#ifndef BACKGROUND_HPP_
    #define BACKGROUND_HPP_


/**
 * @brief Background class to handle the background and the parallax
 */
class Background {
    public:
        enum BACKGROUND_MOVE_TYPE {
            NONE = 0,
            MOVE_X = 1,
            MOVE_Y = 2,
            PARALLAX = 3,
            PARALLAX_X = 4,
            PARALLAX_Y = 5
        };

        /**
         * @brief Construct a new Background object
         */
        Background(void);

        /**
         * @brief Construct a new Background object
         */
        Background(std::string const &path);

        /**
         * @brief Construct a new Background object
         */
        Background(std::string const &path, std::size_t win_width, std::size_t win_height);

        /**
         * @brief Construct a new Background object
         */
        Background(std::string const &path, std::size_t win_width, std::size_t win_height, double speed);

        /**
         * @brief Destroy the Background object
         */
        ~Background();

        /**
         * @brief Set the window dimensions
         */
        void setWindowDimensions(std::size_t win_width, std::size_t win_height);

        /**
         * @brief Get the speed on the y axis of the background
         */
        double getSpeed(void) const;

        /**
         * @brief Set the speed on the y axis of the background
         */
        void setSpeed(double speed);

        /**
         * @brief Update the position of the background based on his type and the timestamp and the mod of the background
         */
        void update_position(std::time_t timestamp);

        /**
         * @brief Draw the background
         */
        void draw(void); 

        /**
         * @brief Set the texture of the background
         */
        void set_texture(std::string const &path);

        /**
         * @brief resize the background
         */
        void resize_x(float x, bool preserve_aspect_ratio = false);

        /**
         * @brief resize the background
         */
        void resize_y(float y, bool preserve_aspect_ratio = false);

        /**
         * @brief resize the background
         */
        void auto_resize_x(void);

        /**
         * @brief resize the background
         */
        void auto_resize_y(void);

        /**
         * @brief Define if the background should repeat 
         */
        void loop(bool repeat);

        /**
         * @brief Define the move type of the background
         */
        void setMoveType(BACKGROUND_MOVE_TYPE move_type);

        /**
         * @brief Define the function to get the point to follow in case of parralax mode
         */
        void setParallaxPos(std::function<raylib::Vector2(void)> const &get_parallax_pos);

    private:

        /**
         * @brief Update the position of the background based on the timestamp
         * @param timestamp the timestamp
         */
        void move(std::size_t timestamp);

        /**
         * @brief Set the background to a new position, similar to 
         */
        void setParallax();


        raylib::Sprite _background;
        double _speed;
        std::size_t _win_width;
        std::size_t _win_height;

        bool _repeat;
        std::function<raylib::Vector2(void)> _get_parallax_pos;
        BACKGROUND_MOVE_TYPE _move_type;

};

#endif /* !BACKGROUND_HPP_ */

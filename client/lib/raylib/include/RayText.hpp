/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** RayText
*/

#include <string>

#ifndef RAYTEXT_HPP_
    #define RAYTEXT_HPP_

namespace raylib
{
    #include "raylib.h"
/**
 * @brief Text class using raylib
 */
class RayText {
    public:
        // Constructor
        /**
         * @brief Construct a new RayText object
         * 
         * @param text the text to display
         * @param x the x position of the text
         * @param y the y position of the text
         * @param size the size of the text
         * @param color the color of the text
         */
        RayText(std::string text, int x, int y, int size, Color color);

        // Destructor
        ~RayText();

        // Setters
        /**
         * @brief Set the text
         * 
         * @param text the text to display
         */
        void setText(std::string text);

        /**
         * @brief Set the position of the text
         * 
         * @param x the x position of the text
         * @param y the y position of the text
         */
        void setPosition(int x, int y);

        /**
         * @brief Set the size of the text
         * 
         * @param size the size of the text
         */
        void setSize(int size);

        // Getters

        /**
         * @brief Get the text
         * 
         * @return the text
         */
        std::string const &getText() const;

        /**
         * @brief Get the size of the text
         * 
         * @return the size of the text
         */
        int getSize(void) const;

        /**
         * @brief Get the x position of the text
         * 
         * @return the x position of the text
         */
        int getX() const;

        /**
         * @brief Get the y position of the text
         * 
         * @return the y position of the text
         */
        int getY() const;

        // Display method
        /**
         * @brief Draw the text
         */
        void draw() const;

        // Overload
        /**
         * @brief Overload of the == operator
         * 
         * @param other the RayText to compare
         * @return true if the RayText are equals
         */
        bool operator==(const RayText &other) const;

        /**
         * @brief Overload of the != operator
         * 
         * @param other the RayText to compare
         * @return true if the RayText are not equals
         */
        bool operator!=(const RayText &other) const;

        /**
         * @brief Overload of the < operator
         * 
         * @param other the RayText to compare
         * @return true if the RayText is less than the other
         */
        bool operator<(const RayText &other) const;

        /**
         * @brief Overload of the > operator
         * 
         * @param other the RayText to compare
         * @return true if the RayText is greater than the other
         */
        bool operator>(const RayText &other) const;

    private:
        std::string _text;
        int _x, _y;
        int _size;
        Color _color;
};

}

#endif /* !RAYTEXT_HPP_ */

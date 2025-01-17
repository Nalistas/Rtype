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
        RayText(std::string text, int x, int y, int size, Color color);

        // Destructor
        ~RayText();

        // Setters
        void setText(std::string text);
        void setPosition(int x, int y);
        void setSize(int size);

        // Getters
        std::string const &getText() const;
        int getSize(void) const;
        int getX() const;
        int getY() const;

        // Display method
        void draw() const;

    private:
        std::string _text;
        int _x, _y;
        int _size;
        Color _color;
};

}

#endif /* !RAYTEXT_HPP_ */

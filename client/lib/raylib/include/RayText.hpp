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
 * @brief Sound class using raylib
 */
class RayText {
    public:
        RayText(std::string text);
        ~RayText();
        void setText(std::string text);
        void display();

    protected:
    private:
        // Font _font;
        std::string _text;
};
}

#endif /* !RAYTEXT_HPP_ */

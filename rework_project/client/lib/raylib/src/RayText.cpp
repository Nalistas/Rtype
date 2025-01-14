/*
** EPITECH PROJECT, 2025
** mirror-rtype
** File description:
** RayText
*/

#include "RayText.hpp"

raylib::RayText::RayText(std::string text) : _text(text)
{
}

raylib::RayText::~RayText()
{
}

void raylib::RayText::display()
{
    DrawText(_text.c_str(), 10, 10, 20, BLACK);
}

void raylib::RayText::setText(std::string text)
{
    _text = text;
}

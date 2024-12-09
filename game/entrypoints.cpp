/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** entrypoint
*/

#include <memory>
#include "IDisplay.hpp"
#include "IGame.hpp"
#include "Rtype.hpp"


extern "C" std::unique_ptr<rtype::IDisplay> displayElement(void)
{
    return std::unique_ptr<RtypeGraphics>();
}

extern "C" std::unique_ptr<rtype::IGame> gameElement(void)
{
    return std::make_unique<Rtype>();
}

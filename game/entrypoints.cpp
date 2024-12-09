/*
** EPITECH PROJECT, 2024
** Rtype
** File description:
** entrypoint
*/

#include <memory>
#include "IGame.hpp"
#include "Rtype.hpp"
#include "isystem.hpp"

extern "C" std::unique_ptr<rtype::IGame> gameElement(void)
{
    return std::make_unique<Rtype>();
}

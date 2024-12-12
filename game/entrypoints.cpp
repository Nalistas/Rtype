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
#include <iostream>

extern "C" std::unique_ptr<rtype::IGame> gameElement(void)
{
    std::cout << "Hello there, the dynamic library has been loaded !" << std::endl;
    return std::make_unique<Rtype>();
}

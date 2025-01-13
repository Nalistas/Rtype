/*
** EPITECH PROJECT, 2024
** poolD11
** File description:
** IDirectoryLister
*/

#include "IDirectoryLister.hpp"
#include <exception>
#include <string>
#include <cstring>

const char *IDirectoryLister::OpenFailureException::what(void) const noexcept
{
    return strerror(errno);
}

const char *IDirectoryLister::NoMoreFileException::what(void) const noexcept
{
    return "End of stream";
}

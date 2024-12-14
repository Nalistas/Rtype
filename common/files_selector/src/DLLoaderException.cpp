/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** DLLoaderException
*/

#include "DLLoader.hpp"

DLLdr::DLLoaderException::DLLoaderException(DLLdr::DLLoaderExcepId id) :
m_id(id)
{}

const char *DLLdr::DLLoaderException::what(void) const noexcept
{
    if (m_id == LibNotOpened)
        return "Library not opened";

    if (m_id == SymNotFound)
        return "Symbol not found";

    if (m_id == SymTypeMismatch)
        return "Symbol type mismatch";
    return "Unknown error";
}
/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** main
*/

#include <iostream>
#include "Rtype_sc.hpp"
#include "RtypeBuilder.hpp"

int main()
{
    // Vérifier la plateforme
    #ifdef WIN32
        std::cout << "Running on Windows platform." << std::endl;
    #else
        std::cout << "Running on Linux platform." << std::endl;
    #endif

    RtypeBuilder rtype_builder;
    Rtype_sc rtype_sc = rtype_builder.build("../sclient.conf");
    std::cout << "Well done" << std::endl;
    rtype_sc = rtype_builder.build("../server.conf");
    std::cout << "Well done" << std::endl;
    return 0;
}

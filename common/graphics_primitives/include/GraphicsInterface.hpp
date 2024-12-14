/*
** EPITECH PROJECT, 2024
** rtype
** File description:
** GraphicsInterface
*/

#include <string>
#include <vector>

#ifndef GRAPHICSINTERFACE_HPP_
    #define GRAPHICSINTERFACE_HPP_


namespace graphics_interface {

    class IGraphicsInterface {
        public:
            virtual ~IGraphicsInterface() = default;
            virtual std::vector<char> encode(void) = 0;
            virtual void decode(std::vector<char> const &) = 0;
    };
}

#endif /* !GRAPHICSINTERFACE_HPP_ */

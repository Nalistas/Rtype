/*
** EPITECH PROJECT, 2024
** poolD11
** File description:
** IDirectoryLister
*/

#include <iostream>

#ifndef IDIRECTORYLISTER_HPP_
    #define IDIRECTORYLISTER_HPP_

class IDirectoryLister
{
    public:
        virtual bool open(const std::string& path, bool hidden) = 0;
        virtual std::string get() = 0;
        virtual bool isGood(void) const = 0;

        class OpenFailureException : public std::exception
        {
            public:
                const char *what(void) const noexcept override;
        };
        class NoMoreFileException : public std::exception
        {
            public :
                const char *what(void) const noexcept override;
        };
};

#endif /* !IDIRECTORYLISTER_HPP_ */

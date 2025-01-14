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
        /**
         * @brief Open the directory lister
         * @param path the path of the directory
         * @param hidden if true, show hidden files
         */
        virtual bool open(const std::string& path, bool hidden) = 0;

        /**
         * @brief Get the next file
         * @return std::string the name of a file
         */
        virtual std::string get() = 0;

        /**
         * @brief Check if the directory lister is good, then it will go to the next file
         * @return true if the directory lister is good
         */
        virtual bool isGood(void) const = 0;

        class OpenFailureException : public std::exception
        {
            public:
                /**
                 * @brief Get the error message
                 * @return const char* the error message
                 */
                const char *what(void) const noexcept override;
        };
        class NoMoreFileException : public std::exception
        {
            public :
                /**
                 * @brief Get the error message
                 * @return const char* the error message
                 */
                const char *what(void) const noexcept override;
        };
};

#endif /* !IDIRECTORYLISTER_HPP_ */

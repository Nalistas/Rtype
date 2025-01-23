/*
** EPITECH PROJECT, 2024
** poolD11
** File description:
** IDirectoryLister
*/

#include <iostream>

#ifndef IDIRECTORYLISTER_HPP_
    #define IDIRECTORYLISTER_HPP_

/**
 * @brief The IDirectoryLister class
 * This class is used to list the files in a directory
 */
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

        /**
         * @brief OpenFailureException class
         * This class is used to throw an exception when the directory lister can't open the directory
         */
        class OpenFailureException : public std::exception
        {
            public:
                /**
                 * @brief Get the error message
                 * @return const char* the error message
                 */
                const char *what(void) const noexcept override;
        };

        /**
         * @brief NoMoreFileException class
         * This class is used to throw an exception when there are no more files in the directory
         */
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

/*
** EPITECH PROJECT, 2024
** poolD11
** File description:
** SafeDirectoryLister
*/

#include "IDirectoryLister.hpp"
#include <dirent.h>
#include <list>

#ifndef SAFEDIRECTORYLISTER_HPP_
#define SAFEDIRECTORYLISTER_HPP_

class SafeDirectoryLister : public IDirectoryLister {
    public:
        /**
         * @brief Constructor
         * @param path the path of the directory
         * @param hidden if true, show hidden files
         */
        SafeDirectoryLister(const std::string& path, bool hidden);

        /**
         * @brief Constructor
         */
        SafeDirectoryLister();

        /**
         * @brief Destructor
         */
        ~SafeDirectoryLister();

        /**
         * @brief Open the directory lister
         * @param path the path of the directory
         * @param hidden if true, show hidden files
         * @return true if the directory lister is good
         */
        bool open(const std::string& path, bool hidden) override;

        /**
         * @brief Check if the directory lister is good, then it will go to the next file
         * @return true if the directory lister is good
         */
        bool isGood(void) const override;

        /**
         * @brief Get the next file
         * @return std::string the name of a file
         */
        std::string get() override;

    protected:
        DIR *m_dir;
        bool m_showHidden;
        std::list<std::string> m_content;
    private:
};

#endif /* !SAFEDIRECTORYLISTER_HPP_ */

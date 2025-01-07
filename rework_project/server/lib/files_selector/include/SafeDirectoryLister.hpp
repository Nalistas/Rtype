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
        SafeDirectoryLister(const std::string& path, bool hidden);
        SafeDirectoryLister();
        ~SafeDirectoryLister();

        bool open(const std::string& path, bool hidden) override;
        bool isGood(void) const override;
        std::string get() override;

    protected:
        DIR *m_dir;
        bool m_showHidden;
        std::list<std::string> m_content;
    private:
};

#endif /* !SAFEDIRECTORYLISTER_HPP_ */

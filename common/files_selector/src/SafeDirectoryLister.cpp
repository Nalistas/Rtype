/*
** EPITECH PROJECT, 2024
** poolD11
** File description:
** SafeDirectoryLister
*/

#include "SafeDirectoryLister.hpp"

bool SafeDirectoryLister::isGood(void) const
{
    return m_content.size() > 0;
}

std::string SafeDirectoryLister::get()
{
    if (!isGood()) {
        throw NoMoreFileException();
    }

    std::string file = m_content.front();
    m_content.pop_front();
    return file;
}


bool SafeDirectoryLister::open(const std::string& path, bool hidden)
{
    dirent *file;

    m_content.clear();
    m_showHidden = hidden;
    if (m_dir != nullptr) {
        closedir(m_dir);
    }
    m_dir = opendir(path.c_str());
    if (m_dir == nullptr) {
        throw OpenFailureException();
    }
    file = readdir(m_dir);
    while(file != nullptr) {
        if (m_showHidden != true || file->d_name[0] != '.') {
            m_content.push_back(file->d_name);
        }
        file = readdir(m_dir);
    }
    for (std::string elt: m_content) {
        std::cout << elt << std::endl;
    }
    return true;
}

SafeDirectoryLister::SafeDirectoryLister(const std::string& path, bool hidden) :
SafeDirectoryLister()
{
    this->open(path, hidden);
}

SafeDirectoryLister::SafeDirectoryLister(void) :
m_dir(nullptr), m_showHidden(true)
{}

SafeDirectoryLister::~SafeDirectoryLister(void)
{
    if (m_dir != nullptr) {
        closedir(m_dir);
    }
}
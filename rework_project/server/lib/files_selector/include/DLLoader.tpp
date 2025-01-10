/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include <functional>

#if defined(WIN32) || defined(_WIN32)
    #include <windows.h>
#else 
    #include <dlfcn.h>
#endif

template<typename T>
DLLdr::DLLoader<T>::DLLoader() : m_lib(nullptr)
{}

namespace DLLdr {
    template <typename T>
    DLLoader<T>::~DLLoader() {
        close();
    }
}


template<typename T>
void DLLdr::DLLoader<T>::close(void)
{
    if (m_lib != nullptr) {
        #if defined(WIN32) || defined(_WIN32)
            FreeLibrary(static_cast<HMODULE>(m_lib));
        #else
            dlclose(m_lib);
        #endif
        m_lib = nullptr;
    }
}

template<typename T>
void DLLdr::DLLoader<T>::open(std::string const &filename)
{
    close();

    #if defined(WIN32) || defined(_WIN32)
        m_lib = static_cast<void *>(LoadLibraryA(filename.c_str()));
        if (m_lib == nullptr) {
            std::cerr << "Error loading library: " << GetLastError() << std::endl;
            throw DLLdr::DLLoaderException(DLLdr::LibNotOpened);
        }
    #else
        m_lib = dlopen(filename.c_str(), RTLD_LAZY);
        if (m_lib == nullptr) {
            std::cerr << "Error loading library: " << dlerror() << std::endl;
            throw DLLdr::DLLoaderException(DLLdr::LibNotOpened);
        }
    #endif
}

template<typename T>
std::unique_ptr<T> DLLdr::DLLoader<T>::getSym(std::string const &name)
{
    void *sym = nullptr;

    #if defined(WIN32) || defined(_WIN32)
        sym = reinterpret_cast<void *>(GetProcAddress(static_cast<HMODULE>(m_lib), name.c_str()));
        if (sym == nullptr) {
            std::cerr << "Error loading symbol: " << GetLastError() << std::endl;
            throw DLLdr::DLLoaderException(DLLdr::SymNotFound);
        }
    #else
        sym = dlsym(m_lib, name.c_str());
        if (sym == nullptr) {
            std::cerr << dlerror() << std::endl;
            throw DLLdr::DLLoaderException(DLLdr::SymNotFound);
        }
    #endif

    std::function<std::unique_ptr<T>()> entryPoint = reinterpret_cast<std::unique_ptr<T>(*)()>(sym);
    return entryPoint();
}

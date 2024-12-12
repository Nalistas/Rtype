/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** DLLoader
*/

#include "DLLoader.hpp"
#include <functional>

#ifdef WIN32
    #include <windows.h>
#else 
    #include <dlfcn.h>
#endif

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

template<typename T>
DLLdr::DLLoader<T>::DLLoader() : m_lib(nullptr)
{}

template<typename T>
DLLdr::DLLoader<T>::~DLLoader()
{
    close();
}

template<typename T>
void DLLdr::DLLoader<T>::close(void)
{
    if (m_lib != nullptr) {
        #ifdef WIN32
            FreeLibrary(static_cast<HMODULE>(m_lib));
        #else
            dlclose(m_lib);
        #endif
        m_lib = nullptr;
    }
}

template<typename T>
void DLLdr::DLLoader<T>::open(const std::string &filename)
{
    close();

    #ifdef WIN32
        m_lib = static_cast<void *>(LoadLibraryA(filename.c_str()));
        if (m_lib == nullptr) {
            std::cerr << "Error loading library: " << GetLastError() << std::endl;
            throw DLLdr::DLLoaderException(DLLdr::LibNotOpened);
        }
    #else
        m_lib = dlopen(filename.c_str(), RTLD_LAZY);
        if (m_lib == nullptr) {
            std::cerr << dlerror() << std::endl;
            throw DLLdr::DLLoaderException(DLLdr::LibNotOpened);
        }
    #endif
}

template<typename T>
std::unique_ptr<T> DLLdr::DLLoader<T>::getSym(std::string const &name)
{
    void *sym = nullptr;

    #ifdef WIN32
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

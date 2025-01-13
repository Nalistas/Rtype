/*
** EPITECH PROJECT, 2024
** arcade
** File description:
** DLLoader
*/

#include <iostream>
#include <memory>
#include <exception>

#pragma once


#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

namespace DLLdr {

    template<typename T>
    class DLLoader {
        public:
            DLLoader();
            ~DLLoader();

            void open(std::string const &);
            void close(void);
            std::unique_ptr<T> getSym(std::string const &);

        protected:
            void *m_lib;
    };

    enum DLLoaderExcepId {
        LibNotOpened,
        SymNotFound,
        SymTypeMismatch
    };

    class DLLoaderException : public std::exception {
        public:
            const char *what(void) const noexcept override;
            DLLoaderException(DLLoaderExcepId);
        private:
            DLLoaderExcepId m_id;
    };
}

#include "DLLoader.tpp"

 
#endif /* !DLLOADER_HPP_ */

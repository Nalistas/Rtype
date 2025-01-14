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
            /**
             * @brief Construct a new DLLoader object
             */
            DLLoader();

            /**
             * @brief Destroy the DLLoader object
             */
            ~DLLoader();

            /**
             * @brief Open the library
             * @param filename the filename of the library
             */
            void open(std::string const &);

            /**
             * @brief Close the library
             */
            void close(void);

            /**
             * @brief Get the symbol of the library
             * @param name the name of the symbol
             * @return std::unique_ptr<T> the symbol
             */
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
            /**
             * @brief Get the error message
             * @return const char* the error message
             */
            const char *what(void) const noexcept override;

            /**
             * @brief Construct a new DLLoader Exception object
             * @param id the id of the error
             */
            DLLoaderException(DLLoaderExcepId);
        private:
            DLLoaderExcepId m_id;
    };
}

#include "DLLoader.tpp"

 
#endif /* !DLLOADER_HPP_ */

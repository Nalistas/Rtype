/*
** EPITECH PROJECT, 2025
** rework_project
** File description:
** zipper
*/

#ifndef ZIPPER_HPP_
    #define ZIPPER_HPP_

#include "zipper_iterator.hpp"
#include <tuple>
#include <cstddef>

template <class... Containers>
class zipper {
    public:
        using iterator = zipper_iterator<Containers...>;
        using iterator_tuple = typename iterator::iterator_tuple;

        /**
         * @brief Main constructor
         * 
         * @param cs The containers
         */
        zipper(Containers&... cs);

        /**
         * @brief Get the begin iterator
         * @return iterator
         */
        iterator begin();

        /**
         * @brief Get the end iterator
         * @return iterator
         */
        iterator end();

    private:
        /**
         * @brief Compute the size of the zipper
         * @param containers The containers
         */
        static size_t _compute_size(Containers&... containers);

        /**
         * @brief Compute the end iterator
         * @param containers The containers
         */
        static iterator_tuple _compute_end(Containers&... containers);

    private:
        iterator_tuple _begin;
        iterator_tuple _end;
        size_t _size;
};

#include "zipper.tpp"

#endif /* !ZIPPER_HPP_ */

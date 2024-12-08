/*
** EPITECH PROJECT, 2024
** gomoku
** File description:
** Promise
*/

#include "Thread/Mutex.hpp"
#include <memory>

#ifndef PROMISE_HPP_
    #define PROMISE_HPP_

namespace thread {

    template <typename Task, typename Result>
    class ThreadPool;

    /**
     * @brief Promise class, used to get the result of a task
     * @tparam T The type of the result
     * @see thread::ThreadPool
     */
    template <typename T>
    class Promise {
        public:
            /**
             * @brief Construct a new Promise object
             */
            Promise();

            /**
             * @brief Destroy the Promise object
             */
            ~Promise();

            /**
             * @brief Get the result of the task, it will block until the task is finished
             * @return The result of the task when it is finished
             */
            T get();

            /**
             * @brief Set the result of the task
             * @param value The result of the task
             */
            bool isResolved();

        private:
            /**
             * @brief Set the result of the task
             * @param value The result of the task
             */
            void set(T value);

            /**
             * @brief Set the worker of the thread pool as friend
             */
            template <typename Task, typename Result>
            friend class ThreadPool<Task, Result>::Worker;

            std::shared_ptr<std::unique_ptr<T>> _value;
            std::shared_ptr<Mutex> _mutex;
    };
}

#include "Thread/Promise.tpp"

#endif /* !PROMISE_HPP_ */

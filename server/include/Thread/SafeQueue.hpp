/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** SafeQueue
*/


#ifndef SAFEQUEUE_HPP_
    #define SAFEQUEUE_HPP_

    #include "Mutex.hpp"
    #include "ScopeLock.hpp"

    #include <queue>
    #include <functional>

namespace thread {  

    template <typename T>
    class SafeQueue {
        public:
            /**
             * @brief Default constructor
             */
            SafeQueue();

            /**
             * @brief Default destructor
             */
            ~SafeQueue();

            /**
             * @brief Push a value in the queue
             */
            void push(T value);

            /**
             * @brief Pop a value from the queue
             * @return true if the value was successfully popped, otherwise false, if false, it means the queue is empty
             * @note this function block the thread if a tryPop is already in progress, the thread will be unlocked when the other tryPop is finished
             */
            bool tryPop(T &value);

            /**
             * @brief Check if the queue is empty
             */
            bool empty(void);

            /**
             * @brief Get the size of the queue
             */
            size_t size(void);

        private:
            std::queue<T> _queue;
            Mutex _mutex;
    };
}

#include "SafeQueue.tpp"

#endif /* !SAFEQUEUE_HPP_ */

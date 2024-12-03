/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ScopeLock
*/


#ifndef SCOPELOCK_HPP_
    #define SCOPELOCK_HPP_

    #include "Mutex.hpp"

/**
 * @brief ScopeLock class, used to lock a Mutex and unlock it when out of scope, see thread::Mutex
 */
namespace thread {
    class ScopeLock {
        public:
            /**
             * @brief Constructor, lock the given Mutex
             * @param mutex
             */
            ScopeLock(Mutex &mutex);

            /**
             * @brief Destructor, unlock the Mutex
             */
            ~ScopeLock();

            /**
             * @brief Lock the Mutex
             */
            void lock();

            /**
             * @brief Unlock the Mutex
             */
            void unlock();

            /**
             * @brief Try to lock the Mutex, does nothing if the Mutex is already locked and continue to the next instruction
             * @return true if the Mutex was successfully locked BY THIS METHOD, otherwise false
             */
            bool trylock();

        private:
            Mutex &_mutex;
    };
}

#endif /* !SCOPELOCK_HPP_ */

/*
** EPITECH PROJECT, 2024
** plazza
** File description:
** ThreadPool
*/


#ifndef THREADPOOL_HPP_
    #define THREADPOOL_HPP_

    #include "Mutex.hpp"
    #include "SafeQueue.hpp"
    #include "ConditionVariable.hpp"
    #include "Thread/ScopeLock.hpp"
    #include "Thread/Promise.hpp"

    #include <thread>
    #include <functional>
    #include <vector>

namespace thread {
    template <typename Task, typename Result>
    class ThreadPool {


        public:
            ThreadPool(size_t maxThreads = 4);
            ~ThreadPool();


            ////////////////////////////////////////////////////////
            // Functions for the user
            ////////////////////////////////////////////////////////
            /// @name Functions for the user
            /// @{

            /**
             * @brief Run the thread pool
             * @note this function is REALLY important and can be source of deadlocks
             */
            void run();

            /**
             * @brief Stop the thread pool. It will wait until all the running tasks are finished and then join the threads
             */
            void stop();

            /**
             * @brief Wait until all the running tasks are finished then stop the thread pool
             */
            void waitUntilComplete();

            /**
             * @brief Check if the thread pool is running
             */
            bool isRunning();

            /**
             * @brief Add a task to the queue
             * @param args The arguments of the task
             * @return The promise of the task, see thread::Promise
             */
            template <typename... Args>
            Promise<Result> addTask(Args...);

            /// @}
            ////////////////////////////////////////////////////////
            // Statistics
            ////////////////////////////////////////////////////////
            /// @name Statistics
            /// @{

            /**
             * @brief Get the number of busy threads
             */
            size_t getBusyThreads();

            /**
             * @brief Get the number of waiting tasks
             */
            size_t getWaitingTasks();

            /// @}

        private:
            ////////////////////////////////////////////////////////
            // Attributes
            ////////////////////////////////////////////////////////
            SafeQueue<std::pair<Task, Promise<Result>>> _queue;
            std::vector<std::thread> _threads;
            ConditionVariable _cv;
            Mutex _mutex;

            bool _run;
            size_t _maxThreads;
            size_t _busyThreads;


            ////////////////////////////////////////////////////////
            // Functions for the thread
            ////////////////////////////////////////////////////////
            /// @name Functions for the thread
            /// @{

            /**
             * @brief Try to pop a task from the queue
             * @param task the pair of the task and the promise
             * @return True if the task was popped
             */
            bool tryPop(std::pair<Task, Promise<Result>> &task);

            /**
             * @brief Check if the queue is empty
             * @return True if the queue is empty
             */
            bool empty();

            /**
             * @brief Get the number of waiting tasks
             * @return The number of waiting tasks, this directly corresponds to the size of the queue
             */
            size_t nbWaitingTasks();

            /**
             * @brief wait until a task is available
             */
            void waitForTask();

            /**
             * @brief Add a busy thread to the pool counter
             */
            void addThreadIsBusy();

            /**
             * @brief Add a free thread to the pool counter
             */
            void addThreadIsFree();

            /// @}

            ////////////////////////////////////////////////////////
            // Class Worker
            ////////////////////////////////////////////////////////
            class Worker {
                public:
                    Worker(ThreadPool<Task, Result> &pool);
                    ~Worker() = default;

                    /**
                     * @brief The thread function
                     */
                    void operator()();
                private:
                    ThreadPool<Task, Result> &_pool;
            };
    };
}

#include "ThreadPool.tpp"

#endif /* !THREADPOOL_HPP_ */

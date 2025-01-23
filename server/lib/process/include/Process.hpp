#ifndef PROCESS_HPP_
    #define PROCESS_HPP_

    #ifdef _WIN32
        #include <windows.h>
    #endif // _WIN32
    #include <sys/types.h>
    #include <vector>
    #include <functional>
    #include <signal.h>
    #include <unistd.h>
    #include <string>


namespace process {

    /**
     * @brief The Process class
     * This class is used to manage the processes
     */
    class Process {
        public:
            /**
             *  @brief Construct a new Process object
             */
            Process();
            /**
             *  @brief Destroy the Process object
             */
            ~Process();

            #ifndef _WIN32
                /**
                 *  @brief Fork a child process
                 */
                template <typename T, typename... Args>
                void fork(Args...);
            #endif // !_WIN32

            /**
             * @brief launch a child process
             * @param command the command to launch it
             */
            void execProcess(std::vector<std::string> &command);

            /**
             *  @brief Kill a child process
             *  @param ndx The index of the child process to kill
             */
            void killChild(size_t ndx);

            /**
             *  @brief Get the pid of the process
             *  @return pid_t The pid of the process
             */
            pid_t getPid();

        private:
            pid_t _pid;

            #ifdef _WIN32
                std::vector<PROCESS_INFORMATION> _childpids;
            #else
                std::vector<pid_t> _childpids;
            #endif // _WIN32
    };
}

#include "Process.tpp"

#endif /* !PROCESS_HPP_ */

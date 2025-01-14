#ifndef PROCESS_TPP
    #define PROCESS_TPP

    #include "Process.hpp"
    #include <iostream>

#ifndef _WIN32

template <typename T, typename... Args>
void process::Process::fork(Args... args)
{
    std::cout << "forking" << std::endl;
    pid_t pid = ::fork();
    if (pid == 0) {
        _childpids.clear();
        _pid = getpid();
        T obj(std::forward<Args>(args)...);
        exit(0);
    } else {
        _childpids.push_back(pid);
    }
}

#endif // !_WIN32

#endif // !PROCESS_TPP

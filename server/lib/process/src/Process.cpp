#include "Process.hpp"

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
    #include <sys/wait.h>
#endif // _WIN32

process::Process::Process()
{
    _pid = getpid();
}

process::Process::~Process()
{
    for (auto childpid : _childpids) {
        #ifdef _WIN32
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, childpid.dwProcessId);
            std::cout << "Attempting to terminate process with PID " << childpid.dwProcessId << std::endl;
            if (TerminateProcess(hProcess, 0)) {
                std::cout << "Process " << childpid.dwProcessId << " terminated successfully." << std::endl;
            } else {
                DWORD error = GetLastError();
                std::cerr << "Failed to terminate process " << childpid.dwProcessId << ". Error code: " << error << std::endl;
            }
            CloseHandle(hProcess);
        #else
            std::cout << "Attempting to kill process with PID " << childpid << std::endl;
            if (kill(childpid, SIGKILL) == 0) {
                std::cout << "Process " << childpid << " killed successfully." << std::endl;
            } else {
                std::cerr << "Failed to kill process " << childpid << ". Error: " << errno << std::endl;
            }
        #endif
    }
}

pid_t process::Process::getPid()
{
    return _pid;
}

void process::Process::killChild(size_t ndx)
{
    if (ndx >= _childpids.size()) {
        std::cerr << "Error at the child id (it is not a pid)";
        return;
    }
    #ifdef _WIN32
        HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, _childpids[ndx].dwProcessId);
        if (hProcess != NULL) {
            std::cout << "Attempting to terminate process with PID " << _childpids[ndx].dwProcessId << std::endl;
            if (TerminateProcess(hProcess, 0)) {
                std::cout << "Process " << _childpids[ndx].dwProcessId << " terminated successfully." << std::endl;
            } else {
                std::cerr << "Failed to terminate process " << _childpids[ndx].dwProcessId << ". Error: " << GetLastError() << std::endl;
            }
            CloseHandle(hProcess); // Always close the handle
        } else {
            std::cerr << "Failed to open process with ID " << _childpids[ndx].dwProcessId << ". Error: " << GetLastError() << std::endl;
        }
    #else
        std::cout << "Attempting to kill process with PID " << _childpids[ndx] << std::endl;
        if (kill(_childpids[ndx], SIGKILL) == 0) {
            std::cout << "Process " << _childpids[ndx] << " killed successfully." << std::endl;
        } else {
            std::cerr << "Failed to kill process " << _childpids[ndx] << ". Error: " << errno << std::endl;
        }
    #endif
    _childpids.erase(_childpids.begin() + ndx);
}

#ifdef _WIN32

void process::Process::execProcess(std::vector<std::string> &command)
{
    STARTUPINFO si = {};
    si.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;

    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.lpSecurityDescriptor = NULL;  // Utilisation du descripteur de sécurité par défaut
    sa.bInheritHandle = TRUE;

    std::string final_command;

    for (auto s : command) {
        final_command += s + " ";
    }
    if (CreateProcess(NULL, (LPSTR)final_command.data(), &sa, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi )) {
        std::cout << "Process launched successfully\n";
        _childpids.push_back(pi);
    } else {
        std::cerr << "Failed to launch process. Error: " << GetLastError() << "\n";
    }
}

#else

void process::Process::execProcess(std::vector<std::string> &command)
{
    pid_t pid = ::fork();
    std::vector<char *> params(command.size());

    for (std::size_t i = 0; i < command.size(); ++i) {
        params[i] = command[i].data();
    }

    if (pid == 0) {
        _childpids.clear();
        _pid = getpid();
        execvp(params[0], params.data());
        perror("execvp failed");
        exit(84);
    } else if (pid > 0) {
        _childpids.push_back(pid);
    } else {
        perror("fork failed");
    }
}

#endif // _WIN32

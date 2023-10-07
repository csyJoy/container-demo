#include <iostream>
#include <mini_container/Cmd/Cmd.hpp>
#include <sys/wait.h>
#include <unistd.h>

Exception<std::monostate> RunCmd::run() noexcept {
    pid_t pid = fork();
    if (pid == 0) {
        char **arg = &args[0];
        execve(arg[0], arg, NULL);
    } else {
        waitpid(pid, NULL, 0);
    }
    return std::monostate{};
}


#include <iostream>
#include <mini_container/Cmd/Cmd.hpp>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

Exception<std::monostate> RunCmd::run() noexcept {
    char *stack = (char *)mmap(NULL, RunCmd::stackSize, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    pid_t pid = clone(setAndRun, stack + RunCmd::stackSize,
                      CLONE_NEWUTS | SIGCHLD, &args[0]);
    waitpid(pid, NULL, 0);
    return std::monostate{};
}

int RunCmd::setAndRun(void *args) {
    char **innerArg = (char **)args;
    execve(innerArg[0], innerArg, NULL);
    return 0;
}

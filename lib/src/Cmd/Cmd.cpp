#include <err.h>
#include <iostream>
#include <mini_container/Cmd/Cmd.hpp>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <sys/wait.h>
#include <unistd.h>

Exception<std::monostate> RunCmd::run() noexcept {
    char *stack = (char *)mmap(NULL, RunCmd::stackSize, PROT_READ | PROT_WRITE,
                               MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
    pid_t pid = clone(setAndRun, stack + RunCmd::stackSize, SIGCHLD, &args[0]);
    if (pid == -1)
        err(EXIT_FAILURE, "clone");
    waitpid(pid, NULL, 0);
    return std::monostate{};
}

int RunCmd::setAndRun(void *args) {
    char **innerArg = (char **)args;
    unshare(CLONE_NEWUTS);
    sethostname("root", 4);
    execve(innerArg[0], innerArg, NULL);
    return 0;
}

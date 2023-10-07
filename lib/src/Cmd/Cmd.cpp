#include <err.h>
#include <iostream>
#include <mini_container/Cmd/Cmd.hpp>
#include <sys/mman.h>
#include <sys/mount.h>
#include <sys/stat.h>
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
    unshare(CLONE_NEWUTS | CLONE_NEWNS);
    RunCmd::chRoot();
    RunCmd::setHostname("root");
    execve(innerArg[0], innerArg, NULL);
    return 0;
}

void RunCmd::setHostname(const std::string &name) {
    sethostname(name.c_str(), name.size());
}

void RunCmd::chRoot() {
    const char *new_root = "/home/csy/container/fake_root";
    const char *put_old = "/oldrootfs";
    char path[10000];
    if (mount(NULL, "/", NULL, MS_REC | MS_PRIVATE, NULL) == -1)
        err(EXIT_FAILURE, "mount-MS_PRIVATE");

    if (mount(new_root, new_root, NULL, MS_BIND, NULL) == -1)
        err(EXIT_FAILURE, "mount-MS_BIND");

    snprintf(path, sizeof(path), "%s/%s", new_root, put_old);
    if (mkdir(path, 0777) == -1)
        err(EXIT_FAILURE, "mkdir");
    if (syscall(SYS_pivot_root, new_root, path) == -1)
        err(EXIT_FAILURE, "pivot_root");

    if (chdir("/") == -1)
        err(EXIT_FAILURE, "chdir");

    if (umount2(put_old, MNT_DETACH) == -1)
        perror("umount2");
    if (rmdir(put_old) == -1)
        perror("rmdir");
}

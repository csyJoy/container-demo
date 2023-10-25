#pragma once

#include <memory>
#include <mini_container/Error/Error.hpp>
#include <optional>
#include <vector>
#include <mini_container/Cgroup/CGroupEntry.hpp>

struct Cmd {
    virtual Exception<std::monostate> run() = 0;
    virtual ~Cmd() = default;
};

struct RunCmd : public Cmd {
    std::string command;
    std::vector<char *> args;
    std::vector<CGroupEntry> cgv;
    const static size_t stackSize = 1024 * 1024;
    RunCmd(){};
    ~RunCmd() override = default;
    template <typename C, typename Args, typename CGV>
    RunCmd(C &&command, Args &&args, CGV &&cgv)
        : command{std::forward<C &&>(command)},
          args{std::forward<Args &&>(args)}, cgv{cgv} {};
    Exception<std::monostate> run() noexcept override;
    void doControl(int pid);
    void cancelControl(int pid);
    static int setAndRun(void *);
    static void chRoot();
    static void setHostname(const std::string &hostname);
};

std::optional<std::unique_ptr<Cmd>> parse(int argc, char **argv) noexcept;

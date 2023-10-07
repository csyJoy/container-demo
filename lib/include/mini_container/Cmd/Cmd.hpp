#pragma once

#include <memory>
#include <mini_container/Error/Error.hpp>
#include <optional>
#include <vector>

struct Cmd {
    virtual Exception<std::monostate> run() = 0;
};

struct RunCmd : public Cmd {
    std::string command;
    std::vector<char *> args;
    RunCmd(){};
    template <typename C, typename Args>
    RunCmd(C &&command, Args &&args)
        : command{std::forward<C &&>(command)},
          args{std::forward<Args &&>(args)} {};
    Exception<std::monostate> run() noexcept override;
};

std::optional<std::unique_ptr<Cmd>> parse(int argc, char **argv) noexcept;

#include "mini_container/Cgroup/CGroupEntry.hpp"
#include <memory>
#include <mini_container/Cmd/Cmd.hpp>
#include <optional>
#include <cstring>
#include <string>

std::optional<std::unique_ptr<Cmd>> parse(int argc, char **argv) noexcept {
    std::string command = argv[1];
    if (command == "run") {
        std::vector<char *> args;
        std::vector<CGroupEntry> cgv;
        for (size_t i = 2; i < argc; i++) {
            if (::strcmp(argv[i], "-m") == 0) {
                i++;
                cgv.push_back(MemMax{std::stoi(argv[i])});
                continue;
            }
            args.push_back(argv[i]);
        }
        return std::make_unique<RunCmd>(std::move(command), std::move(args),
                                        std::move(cgv));
    } else {
        return std::nullopt;
    }
}

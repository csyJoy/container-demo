#include <memory>
#include <mini_container/Cmd/Cmd.hpp>
#include <optional>

std::optional<std::unique_ptr<Cmd>> parse(int argc, char **argv) noexcept {
    std::string command = argv[1];
    if (command == "run") {
        std::vector<char *> args;
        for (size_t i = 2; i < argc; i++) {
            args.push_back(argv[i]);
        }
        return std::make_unique<RunCmd>(std::move(command), std::move(args));
    } else {
        return std::nullopt;
    }
}

#include <iostream>
#include <mini_container/Cmd/Cmd.hpp>

int main(int argc, char **argv) {
    if (auto cmd = parse(argc, argv)) {
        auto err = (*cmd)->run();
        try {
            auto res = std::get<std::monostate>(err);
        } catch (const std::exception &ex) {
            std::cout << std::get<std::string>(err) << std::endl;
        }
    }
    return 0;
}

#include <mini_container/Cmd/Cmd.hpp>

int main(int argc, char **argv) {
    auto r = parse(argc, argv);
    r.value()->run();
}

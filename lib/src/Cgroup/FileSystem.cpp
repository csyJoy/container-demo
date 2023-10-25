#include <fstream>
#include <mini_container/Cgroup/FileSystem.hpp>
#include <filesystem>
#include <iostream>

const std::string CGHelper::cgRoot = "/sys/fs/cgroup/";

void CGHelper::newCGroup(const std::string &name) {
    if (!std::filesystem::is_directory(cgRoot + name)) {
        std::filesystem::create_directories(cgRoot + name);
    }
}

void CGHelper::deleteCGroup(const std::string &name) {
    if (std::filesystem::is_directory(cgRoot + name)) {
        std::filesystem::remove(cgRoot + name);
    }
}

void CGHelper::attachPid(const std::string &name, int pid) {
    checkCGroup(name);
    std::cout << "attach pid " << pid << std::endl;
    std::ofstream ofs{cgRoot + name + "/" + "cgroup.procs",
                      std::ios_base::out | std::ios_base::app};
    ofs << pid << std::endl;
}

void CGHelper::setMemMax(const std::string &name, int m) {
    checkCGroup(name);
    std::cout << "set mem.max" << m << std::endl;
    std::ofstream ofs{cgRoot + name + "/" + "memory.max", std::ios_base::out};
    ofs << m;
}

void CGHelper::checkCGroup(const std::string &name) {
    CGHelper::newCGroup(name);
}

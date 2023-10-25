#include <mini_container/Cgroup/CGroupEntry.hpp>
#include <mini_container/Cgroup/FileSystem.hpp>
#include <fstream>

void CGroupVisitor::operator()(CpuPeriod p) {}

void CGroupVisitor::operator()(CpuQuota q) {}

void CGroupVisitor::operator()(MemMax m) {
    CGHelper::attachPid(this->cgroupName, this->pid);
    CGHelper::setMemMax(this->cgroupName, m.max);
}

CGroupVisitor::CGroupVisitor(const std::string &name, int pid)
    : cgroupName(name), pid(pid) {}

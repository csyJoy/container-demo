#pragma once

#include <variant>
#include <string>

struct CpuPeriod {
    int period;
};

struct CpuQuota {
    int quota;
};

struct MemMax {
    int max;
};

using CGroupEntry = std::variant<CpuPeriod, CpuQuota, MemMax>;

struct CGroupVisitor {
    std::string cgroupName;
    int pid;
    CGroupVisitor(const std::string &, int);
    void operator()(CpuPeriod);
    void operator()(CpuQuota);
    void operator()(MemMax);
};

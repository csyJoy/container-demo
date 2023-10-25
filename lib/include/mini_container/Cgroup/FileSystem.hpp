#pragma once

#include <string>

struct CGHelper {
    static const std::string cgRoot;

    static void newCGroup(const std::string &name);
    static void attachPid(const std::string &name, int pid);
    static void setCpuPeriod(const std::string &name, int period);
    static void setCpuQuota(const std::string &name, int quota);
    static void setMemMax(const std::string &name, int max);
    static void checkCGroup(const std::string &name);
    static void deleteCGroup(const std::string &name);
};

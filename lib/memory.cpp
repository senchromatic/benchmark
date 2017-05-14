#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#include "memory.h"


using std::string;
using Benchmarking::Memory;
constexpr int LINUX_BYTES_PER_KB = 1024;


void Memory::reset() {
    initial = current_usage();
}

Memory::Memory(const long long &num_operations) : n {num_operations} {
    reset();
}

long long Memory::extract_number(const string &line) const {
    string field;
    long long value;
    std::istringstream iss(line);
    iss >> field >> value;
    return value;
}

long long Memory::current_usage() const {
    long long virtual_kb = -1, physical_kb = -1;

    std::ifstream status("/proc/self/status");
    string line;
    while (getline(status, line)) {
        if (line.find("VmSize") != string::npos)
            virtual_kb = extract_number(line);
        if (line.find("VmRSS") != string::npos)
            physical_kb = extract_number(line);
        if (std::min(virtual_kb, physical_kb) >= 0)
            break;
    }
    status.close();

    return virtual_kb + physical_kb;
}

long long Memory::allocated() const {
    return current_usage() - initial;
}

string Memory::report() const {
    double unit = static_cast<double>(allocated() * LINUX_BYTES_PER_KB) / n;
    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << unit << " bytes";
    return oss.str();
}

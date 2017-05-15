#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

#include "memory.h"
#include "type.h"


using std::string;
using Benchmarking::Memory;
using Benchmarking::ll;
constexpr int LINUX_BYTES_PER_KB = 1024;


void Memory::reset() {
    initial = current_usage();
}

Memory::Memory(const ll &num_operations, const size_t sizeof_base) :
            n {num_operations}, base {sizeof_base} {
    reset();
}

ll Memory::extract_number(const string &line) const {
    string field;
    ll value;
    std::istringstream iss(line);
    iss >> field >> value;
    return value;
}

ll Memory::current_usage() const {
    ll virtual_kb = -1, physical_kb = -1;

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

ll Memory::allocated() const {
    return current_usage() - initial;
}

string Memory::report() const {
    ld unit = static_cast<ld>(allocated() * LINUX_BYTES_PER_KB) / n;
    ld overhead = unit - base;

    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << overhead << " bytes";
    return oss.str();
}

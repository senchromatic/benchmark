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

Memory::Memory(const ll &num_operations, const size_t sizeof_data) :
            n {num_operations}, data {sizeof_data} {
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
    ll virtual_kb = -1;

    std::ifstream status("/proc/self/status");
    string line;
    while (getline(status, line)) {
        if (line.find("VmSize") != string::npos) {
            virtual_kb = extract_number(line);
            break;
        }
    }
    status.close();

    return virtual_kb;
}

ll Memory::allocated() const {
    return current_usage() - initial;
}

string Memory::report() const {
    ld unit = static_cast<ld>(allocated() * LINUX_BYTES_PER_KB) / n;
    ld overhead = unit - data;
    if (overhead < 0)
        overhead = 0;

    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << overhead << " byte(s)";
    return oss.str();
}

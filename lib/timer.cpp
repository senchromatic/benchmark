#include <sstream>

#include "timer.h"
#include "type.h"


using Benchmarking::Timer;
using Benchmarking::ll;
constexpr ll NS_PER_SEC = 1e9;


void Timer::reset() {
    start = current_time();
}

Timer::Timer(const ll &num_operations) : n {num_operations} {
    reset();
}

ll Timer::current_time() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    return ts.tv_sec*NS_PER_SEC + ts.tv_nsec;
}

ll Timer::elapsed() {
    return current_time() - start;
}

std::string Timer::report(const ll &base) {
    ld rate = static_cast<ld>(elapsed() - base) / n;

    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << rate << " ns";
    return oss.str();
}

#include <sstream>

#include "timer.h"
#include "type.h"


using Benchmarking::Timer;
using Benchmarking::ll;
constexpr ll NS_PER_SEC = 1e9;


void Timer::reset() {
    start = current_time();
}

Timer::Timer(const ll &num_operations, Timer *timer) : n {num_operations}, other {timer} {
    reset();
}

ll Timer::current_time() const {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);

    return ts.tv_sec*NS_PER_SEC + ts.tv_nsec;
}

void Timer::discount(const Timer &processor) {
    start += processor.elapsed();
}

ll Timer::elapsed() const {
    return current_time() - start;
}

std::string Timer::report(const ll &base) const {
    if (other)
        other->discount(*this);
    
    ld rate = static_cast<ld>(elapsed() - base) / n;
    if (rate < 0)
        rate = 0;

    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << rate << " ns";
    return oss.str();
}

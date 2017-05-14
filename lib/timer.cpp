#include <iostream>
#include <sstream>

#include "timer.h"


using Benchmarking::Timer;
constexpr int NS_PER_SEC = 1e9;


void Timer::reset() {
    start = current_time();
}

Timer::Timer(const long long &num_operations) : n {num_operations} {
    reset();
}

long long Timer::current_time() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec*NS_PER_SEC + ts.tv_nsec;
}

double Timer::elapsed() {
    return current_time() - start;
}

std::string Timer::report() {
    int rate = elapsed() / n;
    std::ostringstream oss;
    oss.precision(2);
    oss << std::fixed << elapsed() / n << " ns";
    return oss.str();
}

#include "timer.h"

using Benchmarking::Timer;


void Timer::reset() {
    start = current_time();
}

Timer::Timer(const long long &num_operations) : n {num_operations} {
    reset();
}

long long Timer::current_time() {
    timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return ts.tv_sec*1e9 + ts.tv_nsec;
}

double Timer::elapsed() {
    return current_time() - start;
}

std::string Timer::report() {
    double rate = elapsed() / n;
    return std::to_string(rate) + " ns";
}

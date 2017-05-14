#ifndef TIMER_H
#define TIMER_H


#include <string>


namespace Benchmarking {

    class Timer {
    public:
        void reset();  // start timer
        Timer(const long long &num_operations);
        std::string report();  // nanoseconds per operation (on average)
    private:
        long long n;  // number of operations performed
        long long start;
        long long current_time();  // nanoseconds since epoch
        long long elapsed();  // nanoseconds since last reset
    };

}


#endif // TIMER_H

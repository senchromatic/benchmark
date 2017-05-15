#ifndef TIMER_H
#define TIMER_H


#include <string>

#include "type.h"


namespace Benchmarking {

    class Timer {
    public:
        void reset();  // start timer
        Timer(const ll &num_operations);
        std::string report();  // nanoseconds per operation (on average)
    private:
        ll n;  // number of operations performed
        ll start;
        ll current_time();  // nanoseconds since epoch
        ll elapsed();  // nanoseconds since last reset
    };

}


#endif // TIMER_H

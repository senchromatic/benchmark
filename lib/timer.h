#ifndef TIMER_H
#define TIMER_H


#include <string>

#include "type.h"


namespace Benchmarking {

    class Timer {
    public:
        void reset();  // start timer
        Timer(const ll &num_operations, Timer *timer);
        void discount(const Timer &processor);  // subtract time
        ll elapsed() const;  // nanoseconds since last reset
        std::string report(const ll &base) const;  // nanoseconds per operation (on average)
    private:
        ll n;  // number of operations performed
        ll start;
        ll current_time() const;  // nanoseconds since epoch
        Timer *other;
    };

}


#endif // TIMER_H

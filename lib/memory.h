#ifndef MEMORY_H
#define MEMORY_H


#include <string>


namespace Benchmarking {

    class Memory {
    public:
        void reset();  // record memory usage
        Memory(const long long &num_operations);
        std::string report() const;  // bytes per element (on average)
    private:
        long long n;  // number of elements in container
        long long initial;
        long long extract_number(const std::string &line) const;
        long long current_usage() const;  // total (= virtual + physical) RAM used by process (in KB)
        long long allocated() const;  // kilobytes allocated since last reset
    };

}

#endif // TIMER_H

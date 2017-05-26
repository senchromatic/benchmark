#ifndef MEMORY_H
#define MEMORY_H


#include <string>

#include "type.h"


namespace Benchmarking {

    class Memory {
    public:
        void reset();  // record memory usage
        Memory(const ll &num_operations, const size_t sizeof_data);
        std::string report() const;  // bytes per element (on average)
    private:
        ll n;  // number of elements in container
        size_t data;  // size of encapsulated data
        ll initial;
        ll extract_number(const std::string &line) const;
        ll current_usage() const;  // total RAM used by process (in KB)
        ll allocated() const;  // kilobytes allocated since last reset
    };

}

#endif // MEMORY_H

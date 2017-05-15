#include <array>
#include <iostream>
#include <vector>

#include "../../lib/memory.h"
#include "../../lib/timer.h"
#include "../../lib/type.h"


using Benchmarking::ld;
using Benchmarking::LD_SIZE;
using Benchmarking::ll;

using Benchmarking::Memory;
using Benchmarking::Timer;

using std::cout;
using std::string;

constexpr ll NUM_ELEMENTS = 1e7;

void test_c_array() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        ld *c = new ld[NUM_ELEMENTS];
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            c[i] = i;
        cout << "c_array[i] =: " << timer.report() << '\n';

        mem = memory.report();
        delete[] c;
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_vector() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::vector<ld> v(NUM_ELEMENTS);
        v.reserve(NUM_ELEMENTS);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            v[i] = i;
        cout << "vector[i] =: " << timer.report() << '\n';

        mem = memory.report();
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}


int main() {
    cout << '\n';

    test_c_array();
    test_vector();

    return 0;
}

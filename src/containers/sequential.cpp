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


void test_c_array(const ll &base) {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        ld *c = new ld[NUM_ELEMENTS];

        Timer timer(NUM_ELEMENTS);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            c[i] = i;
        cout << "c_array[i] = x: " << timer.report(base) << '\n';

        mem = memory.report();
        delete[] c;
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_vector(const ll &base) {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        std::vector<ld> v(NUM_ELEMENTS);

        Timer timer(NUM_ELEMENTS);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            v[i] = i;
        cout << "vector[i] = x: " << timer.report(base) << '\n';

        mem = memory.report();
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}


int main() {
    cout << '\n';

    ld x;
    Timer loop(NUM_ELEMENTS);
    for (ll i = 0; i < NUM_ELEMENTS; i++)
        x = i;
    ll base = loop.elapsed();

    test_c_array(base);
    test_vector(base);

    cout << '\n';
    return 0;
}

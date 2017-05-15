#include <array>
#include <fstream>
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

using std::string;

constexpr ll NUM_ELEMENTS = 1e7;

ll base = 0;
std::ofstream fout("logs/sequential.txt");


void test_c_array() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        ld *c = new ld[NUM_ELEMENTS];

        Timer timer(NUM_ELEMENTS);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            c[i] = i;
        fout << "c_array[i] = x: " << timer.report(base) << '\n';

        mem = memory.report();
        delete[] c;
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_vector() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        std::vector<ld> v(NUM_ELEMENTS);

        Timer timer(NUM_ELEMENTS);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            v[i] = i;
        fout << "vector[i] = x: " << timer.report(base) << '\n';

        mem = memory.report();
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}


int main() {
    ld x;
    Timer loop(NUM_ELEMENTS);
    for (ll i = 0; i < NUM_ELEMENTS; i++)
        x = i;
    base = loop.elapsed();

    test_c_array();
    test_vector();

    return 0;
}

#include <array>
#include <iostream>
#include <vector>

#include "../../lib/memory.h"
#include "../../lib/timer.h"


using Benchmarking::Memory;
using Benchmarking::Timer;
using std::cout;
using std::string;

constexpr long NUM_ELEMENTS = 1e8;


void test_c_array() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS);
        Timer timer(NUM_ELEMENTS);

        int *c = new int[NUM_ELEMENTS];
        for (int i = 0; i < NUM_ELEMENTS; i++)
            c[i] = i;
        cout << "c_array[i] = i: " << timer.report() << '\n';

        mem = memory.report();
        delete[] c;
    }
    cout << "total time: " << total.report() << '\n';

    cout << "memory: " << mem << "\n\n";
}

void test_vector() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS);
        Timer timer(NUM_ELEMENTS);

        std::vector<int> v(NUM_ELEMENTS);
        v.reserve(NUM_ELEMENTS);
        for (int i = 0; i < NUM_ELEMENTS; i++)
            v[i] = i;
        cout << "vector[i] = i: " << timer.report() << '\n';

        mem = memory.report();
    }
    cout << "total time: " << total.report() << '\n';

    cout << "memory: " << mem << "\n\n";
}


int main() {
    cout << '\n';

    test_c_array();
    test_vector();

    return 0;
}

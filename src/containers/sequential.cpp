#include <array>
#include <iostream>
#include <vector>

#include "../../lib/timer.h"


using Benchmarking::Memory;
using Benchmarking::Timer;
using std::cout;

constexpr long NUM_ELEMENTS = 1e8;


void test_c_array() {

    Timer total(NUM_ELEMENTS);
    {
        Timer timer(NUM_ELEMENTS);

        int *c = new int[NUM_ELEMENTS];
        for (int i = 0; i < NUM_ELEMENTS; i++)
            c[i] = i;

        cout << "c_array[i] = i: " << timer.report() << '\n';
        delete[] c;
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_vector() {

    Timer total(NUM_ELEMENTS);
    {
        Timer timer(NUM_ELEMENTS);

        std::vector<int> v(NUM_ELEMENTS);
        for (int i = 0; i < NUM_ELEMENTS; i++)
            v[i] = i;

        cout << "vector[i] = i: " << timer.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}


int main() {
    cout << '\n';

    test_c_array();
    test_vector();

    return 0;
}

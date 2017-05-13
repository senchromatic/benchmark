#include <iostream>
#include <array>
#include <vector>

#include "../lib/timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long num_elements = 1e6;


void test_c_array() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        int *c = new int[num_elements];
        for (int i = 0; i < num_elements; i++)
            c[i] = i;

        cout << "c_array[i] = i: " << t.report() << "\n";
        delete[] c;
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_vector() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::vector<int> v(num_elements);
        for (int i = 0; i < num_elements; i++)
            v[i] = i;

        cout << "vector[i] = i: " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_cpp_array() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::array<int, num_elements> cpp;
        for (int i = 0; i < num_elements; i++)
            cpp[i] = i;

        cout << "cpp_array[i] = i: " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}


int main() {
    cout << "\n";

    test_c_array();
    test_vector();
    test_cpp_array();

    return 0;
}

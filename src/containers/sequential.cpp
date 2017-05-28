#include <fstream>
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
constexpr ll base = 0;

std::ofstream fout("logs/sequential.txt");


void test_c_array() {
    string mem;

    Timer excess(NUM_ELEMENTS, nullptr);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        ld *c = new ld[NUM_ELEMENTS];
        
        Timer timer(NUM_ELEMENTS, &excess);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            c[i] = i;
        fout << "c_array[i] = x: " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();
        
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            ++c[i];
        fout << "++c_array[i]: " << timer.report(base) << '\n';
        
        timer.reset();
        
        ld *p = c, *last = c+NUM_ELEMENTS;
        while (p++ < last)
            ++(*p);
        fout << "++(*c_array++): " << timer.report(base) << '\n';
        
        delete[] c;
    }
    fout << "excess time: " << excess.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_vector() {
    string mem;

    Timer excess(NUM_ELEMENTS, nullptr);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        std::vector<ld> v(NUM_ELEMENTS);
        
        Timer timer(NUM_ELEMENTS, &excess);
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            v[i] = i;
        fout << "vector[i] = x: " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();
        
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            ++v[i];
        fout << "++vector[i]: " << timer.report(base) << '\n';
        
        timer.reset();
        
        for (ll i = 0; i < NUM_ELEMENTS; i++)
            ++v.at(i);
        fout << "++vector.at(i): " << timer.report(base) << '\n';
        
        timer.reset();
             
        for (auto &x : v)
            ++x;
        fout << "++(&x : vector): " << timer.report(base) << '\n';
        
        timer.reset();
        
        for (auto it = v.begin(); it != v.end(); ++it)
            ++(*it);
        fout << "++vector::iterator: " << timer.report(base) << '\n';
    }
    fout << "excess time: " << excess.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}


int main() {
    test_c_array();
    test_vector();

    return 0;
}

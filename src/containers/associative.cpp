#include <cassert>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "../../lib/memory.h"
#include "../../lib/timer.h"
#include "../../lib/type.h"


using Benchmarking::ld;
using Benchmarking::LD_SIZE;
using Benchmarking::ll;

using Benchmarking::Memory;
using Benchmarking::Timer;

using std::string;

constexpr ll NUM_ELEMENTS = 1e6;
constexpr bool PARANOIA = false;

ll base = 0;
std::ofstream fout("logs/associative.txt");


void test_unordered_set() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::unordered_set<ld> s;
        s.reserve(NUM_ELEMENTS);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.insert(x);
        fout << "unordered_set.insert(x): " << timer.report(base) << '\n';

        mem = memory.report();
        if (PARANOIA)
            assert(s.size() == NUM_ELEMENTS);
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.erase(s.find(x));
        fout << "unordered_set.erase(x): " << timer.report(0) << '\n';

        if (PARANOIA)
            assert(s.empty());
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_unordered_map() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::unordered_map<ld, bool> m;
        m.reserve(NUM_ELEMENTS);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m[x];
        fout << "unordered_map.insert(x): " << timer.report(base) << '\n';

        mem = memory.report();
        if (PARANOIA)
            assert(m.size() == NUM_ELEMENTS);
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m.erase(m.find(x));
        fout << "unordered_map.erase(x): " << timer.report(0) << '\n';

        if (PARANOIA)
            assert(m.empty());
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_set() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::set<ld> s;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.insert(x);
        fout << "set.insert(x): " << timer.report(base) << '\n';

        mem = memory.report();
        if (PARANOIA)
            assert(s.size() == NUM_ELEMENTS);
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.erase(s.find(x));
        fout << "set.erase(x): " << timer.report(0) << '\n';

        if (PARANOIA)
            assert(s.empty());
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_map() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::map<ld, bool> m;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m[x];
        fout << "map.insert(x): " << timer.report(base) << '\n';

        mem = memory.report();
        if (PARANOIA)
            assert(m.size() == NUM_ELEMENTS);
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m.erase(m.find(x));
        fout << "map.erase(m.find(x)): " << timer.report(0) << '\n';

        if (PARANOIA)
            assert(m.empty());
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}


int main() {
    Timer loop(NUM_ELEMENTS);
    for (ld x = 0; x < NUM_ELEMENTS; x++);
    base = loop.elapsed();

    test_unordered_set();
    test_unordered_map();
    test_set();
    test_map();

    return 0;
}

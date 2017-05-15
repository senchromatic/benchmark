#include <cassert>
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

using std::cout;
using std::string;

constexpr ll NUM_ELEMENTS = 1e6;


void test_unordered_set(const ll &base) {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::unordered_set<ld> s;
        s.reserve(NUM_ELEMENTS);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.insert(x);
        cout << "unordered_set.insert(): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.erase(s.find(x));
        cout << "unordered_set.erase(): " << timer.report(0) << '\n';
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_unordered_map(const ll &base) {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::unordered_map<ld, bool> m;
        m.reserve(NUM_ELEMENTS);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m[x];
        cout << "unordered_map.insert(): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m.erase(m.find(x));
        cout << "unordered_map.erase(): " << timer.report(0) << '\n';
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_set(const ll &base) {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::set<ld> s;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.insert(x);
        cout << "set.insert(): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            s.erase(s.find(x));
        cout << "set.erase(): " << timer.report(0) << '\n';

        assert(s.empty());
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_map(const ll &base) {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::map<ld, bool> m;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m[x];
        cout << "map.insert(): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        for (ld x = 0; x < NUM_ELEMENTS; x++)
            m.erase(m.find(x));
        cout << "map.erase(m.find(i)): " << timer.report(0) << '\n';

        assert(m.empty());
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}


int main() {
    cout << '\n';

    Timer loop(NUM_ELEMENTS);
    for (ld x = 0; x < NUM_ELEMENTS; x++);
    ll base = loop.elapsed();

    test_unordered_set(base);
    test_unordered_map(base);
    test_set(base);
    test_map(base);

    cout << '\n';
    return 0;
}

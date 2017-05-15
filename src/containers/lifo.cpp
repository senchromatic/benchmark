#include <fstream>
#include <iostream>
#include <list>
#include <queue>
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
std::ofstream fout("logs/lifo.txt");


void test_vector() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::vector<ld> v;
        v.reserve(NUM_ELEMENTS);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            v.push_back(x);
        fout << "vector.push_back(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!v.empty())
            v.pop_back();
        fout << "vector.pop_back(): " << timer.report(0) << '\n';
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_deque() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::deque<ld> d;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            d.push_back(x);
        fout << "deque.push_back(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!d.empty())
            d.pop_back();
        fout << "deque.pop_back(): " << timer.report(0) << '\n';
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_queue() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::queue<ld> q;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            q.push(x);
        fout << "queue.push(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!q.empty())
            q.pop();
        fout << "queue.pop(): " << timer.report(0) << '\n';
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_list() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::list<ld> l;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            l.push_back(x);
        fout << "list.push_back(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!l.empty())
            l.pop_back();
        fout << "list.pop_back(): " << timer.report(0) << '\n';
    }
    fout << "total time: " << total.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}


int main() {
    Timer loop(NUM_ELEMENTS);
    for (ld x = 0; x < NUM_ELEMENTS; x++);
    base = loop.elapsed();

    test_vector();
    test_deque();
    test_queue();
    test_list();

    return 0;
}

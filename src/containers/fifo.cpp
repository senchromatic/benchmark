#include <fstream>
#include <iostream>
#include <list>
#include <stack>
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
std::ofstream fout("logs/fifo.txt");


void test_deque() {
    string mem;

    Timer excess(NUM_ELEMENTS, nullptr);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        std::deque<ld> d;

        Timer timer(NUM_ELEMENTS, &excess);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            d.push_front(x);
        fout << "deque.push_front(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!d.empty())
            d.pop_front();
        fout << "deque.pop_front(): " << timer.report(0) << '\n';
    }
    fout << "excess time: " << excess.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_stack() {
    string mem;

    Timer excess(NUM_ELEMENTS, nullptr);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        std::stack<ld> q;
        
        Timer timer(NUM_ELEMENTS, &excess);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            q.push(x);
        fout << "stack.push(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!q.empty())
            q.pop();
        fout << "stack.pop(): " << timer.report(0) << '\n';
    }
    fout << "excess time: " << excess.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}

void test_list() {
    string mem;

    Timer excess(NUM_ELEMENTS, nullptr);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        std::list<ld> l;
        
        Timer timer(NUM_ELEMENTS, &excess);
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            l.push_front(x);
        fout << "list.push_front(x): " << timer.report(base) << '\n';

        mem = memory.report();
        timer.reset();

        while (!l.empty())
            l.pop_front();
        fout << "list.pop_front(): " << timer.report(0) << '\n';
    }
    fout << "excess time: " << excess.report(base) << '\n';

    fout << "overhead memory: " << mem << "\n\n";
}


int main() {
    Timer loop(NUM_ELEMENTS, nullptr);
    for (ld x = 0; x < NUM_ELEMENTS; x++);
    base = loop.elapsed();

    test_deque();
    test_stack();
    test_list();

    return 0;
}

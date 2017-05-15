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

using std::cout;
using std::string;

constexpr ll NUM_ELEMENTS = 1e7;


void test_deque() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::deque<ld> d;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            d.push_front(x);
        cout << "deque.push_front(): " << timer.report() << "\n";

        mem = memory.report();
        timer.reset();

        while (!d.empty())
            d.pop_front();
        cout << "deque.pop_front(): " << timer.report() << "\n";
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_stack() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::stack<ld> q;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            q.push(x);
        cout << "stack.push(): " << timer.report() << "\n";

        mem = memory.report();
        timer.reset();

        while (!q.empty())
            q.pop();
        cout << "stack.pop(): " << timer.report() << "\n";
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_list() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS, LD_SIZE);
        Timer timer(NUM_ELEMENTS);

        std::list<ld> l;
        for (ld x = 0; x < NUM_ELEMENTS; x++)
            l.push_front(x);
        cout << "list.push_front(): " << timer.report() << "\n";

        mem = memory.report();
        timer.reset();

        while (!l.empty())
            l.pop_front();
        cout << "list.pop_front(): " << timer.report() << "\n";
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}


int main() {
    cout << "\n";

    test_deque();
    test_stack();
    test_list();

    return 0;
}

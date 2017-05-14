#include <iostream>
#include <list>
#include <stack>
#include <vector>

#include "../../lib/memory.h"
#include "../../lib/timer.h"


using Benchmarking::Memory;
using Benchmarking::Timer;
using std::cout;
using std::string;

constexpr long NUM_ELEMENTS = 1e8;


void test_deque() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS);
        Timer timer(NUM_ELEMENTS);

        std::deque<int> d;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            d.push_front(i);
        cout << "deque.push_front(): " << timer.report() << "\n";

        mem = memory.report();
        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            d.pop_front();
        cout << "deque.pop_front(): " << timer.report() << "\n";
    }
    cout << "total time: " << total.report() << '\n';

    cout << "memory: " << mem << "\n\n";
}

void test_stack() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS);
        Timer timer(NUM_ELEMENTS);

        std::stack<int> q;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            q.push(i);
        cout << "stack.push(): " << timer.report() << "\n";

        mem = memory.report();
        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            q.pop();
        cout << "stack.pop(): " << timer.report() << "\n";
    }
    cout << "total time: " << total.report() << '\n';

    cout << "memory: " << mem << "\n\n";
}

void test_list() {
    string mem;

    Timer total(NUM_ELEMENTS);
    {
        Memory memory(NUM_ELEMENTS);
        Timer timer(NUM_ELEMENTS);

        std::list<int> l;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            l.push_front(i);
        cout << "list.push_front(): " << timer.report() << "\n";

        mem = memory.report();
        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            l.pop_front();
        cout << "list.pop_front(): " << timer.report() << "\n";
    }
    cout << "total time: " << total.report() << '\n';

    cout << "memory: " << mem << "\n\n";
}


int main() {
    cout << "\n";

    test_deque();
    test_stack();
    test_list();

    return 0;
}

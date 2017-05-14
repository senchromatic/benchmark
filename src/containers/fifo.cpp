#include <iostream>
#include <list>
#include <stack>
#include <vector>

#include "../../lib/timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long NUM_ELEMENTS = 1e8;


void test_deque() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::deque<int> d;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            d.push_front(i);
        cout << "deque.push_front(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            d.pop_front();
        cout << "deque.pop_front(): " << t.report() << "\n";
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_stack() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::stack<int> q;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            q.push(i);
        cout << "stack.push(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            q.pop();
        cout << "stack.pop(): " << t.report() << "\n";
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_list() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::list<int> l;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            l.push_front(i);
        cout << "list.push_front(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            l.pop_front();
        cout << "list.pop_front(): " << t.report() << "\n";
    }
    cout << "total: " << total.report() << "\n\n";

}


int main() {
    cout << "\n";

    test_deque();
    test_stack();
    test_list();

    return 0;
}

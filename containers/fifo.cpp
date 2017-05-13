#include <iostream>
#include <list>
#include <stack>
#include <vector>

#include "../lib/timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long num_elements = 1e6;


void test_deque() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::deque<int> d;
        for (int i = 0; i < num_elements; i++)
            d.push_front(i);
        cout << "deque.push_front(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            d.pop_front();
        cout << "deque.pop_front(): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_stack() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::stack<int> q;
        for (int i = 0; i < num_elements; i++)
            q.push(i);
        cout << "stack.push(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            q.pop();
        cout << "stack.pop(): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_list() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::list<int> l;
        for (int i = 0; i < num_elements; i++)
            l.push_front(i);
        cout << "list.push_front(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
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

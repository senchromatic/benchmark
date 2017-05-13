#include <iostream>
#include <list>
#include <queue>
#include <vector>

#include "timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long num_elements = 1e6;


void test_vector() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::vector<int> v;
        for (int i = 0; i < num_elements; i++)
            v.push_back(i);
        cout << "vector.push_back(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            v.pop_back();
        cout << "vector.pop_back(): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_deque() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::deque<int> d;
        for (int i = 0; i < num_elements; i++)
            d.push_back(i);
        cout << "deque.push_back(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            d.pop_back();
        cout << "deque.pop_back(): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_queue() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::queue<int> q;
        for (int i = 0; i < num_elements; i++)
            q.push(i);
        cout << "queue.push(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            q.pop();
        cout << "queue.pop(): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_list() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::list<int> l;
        for (int i = 0; i < num_elements; i++)
            l.push_back(i);
        cout << "list.push_back(): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            l.pop_back();
        cout << "list.pop_back(): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}


int main() {
    cout << "\n";

    test_vector();
    test_deque();
    test_queue();
    test_list();

    return 0;
}

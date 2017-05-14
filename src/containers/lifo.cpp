#include <iostream>
#include <list>
#include <queue>
#include <vector>

#include "../../lib/timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long NUM_ELEMENTS = 1e8;


void test_vector() {

    Timer total(NUM_ELEMENTS);
    {
        Timer timer(NUM_ELEMENTS);

        std::vector<int> v;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            v.push_back(i);
        cout << "vector.push_back(): " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            v.pop_back();
        cout << "vector.pop_back(): " << timer.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_deque() {

    Timer total(NUM_ELEMENTS);
    {
        Timer timer(NUM_ELEMENTS);

        std::deque<int> d;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            d.push_back(i);
        cout << "deque.push_back(): " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            d.pop_back();
        cout << "deque.pop_back(): " << timer.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_queue() {

    Timer total(NUM_ELEMENTS);
    {
        Timer timer(NUM_ELEMENTS);

        std::queue<int> q;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            q.push(i);
        cout << "queue.push(): " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            q.pop();
        cout << "queue.pop(): " << timer.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_list() {

    Timer total(NUM_ELEMENTS);
    {
        Timer timer(NUM_ELEMENTS);

        std::list<int> l;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            l.push_back(i);
        cout << "list.push_back(): " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            l.pop_back();
        cout << "list.pop_back(): " << timer.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}


int main() {
    cout << '\n';

    test_vector();
    test_deque();
    test_queue();
    test_list();

    return 0;
}

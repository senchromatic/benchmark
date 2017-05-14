#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "../../lib/timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long NUM_ELEMENTS = 1e6;


void test_unordered_set() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::unordered_set<int> s;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            s.insert(i);
        cout << "unordered_set.insert(i): " << t.report() << '\n';

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            s.erase(s.find(i));
        cout << "unordered_set.erase(unordered_s.find(i)): " << t.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_unordered_map() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::unordered_map<int, int> m;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            m[i] = i;
        cout << "unordered_map[i] = i: " << t.report() << '\n';

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            m.erase(m.find(i));
        cout << "unordered_map.erase(m.find(i)): " << t.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_set() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::set<int> s;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            s.insert(i);
        cout << "set.insert(i): " << t.report() << '\n';

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            s.erase(s.find(i));
        cout << "set.erase(s.find(i)): " << t.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_map() {

    Timer total(NUM_ELEMENTS);
    {
        Timer t(NUM_ELEMENTS);

        std::map<int, int> m;
        for (int i = 0; i < NUM_ELEMENTS; i++)
            m[i] = i;
        cout << "map[i] = i: " << t.report() << '\n';

        t.reset();

        for (int i = 0; i < NUM_ELEMENTS; i++)
            m.erase(m.find(i));
        cout << "map.erase(m.find(i)): " << t.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}


int main() {
    cout << '\n';

    test_unordered_set();
    test_unordered_map();
    test_set();
    test_map();


    return 0;
}

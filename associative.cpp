#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include "timer.h"


using Benchmarking::Timer;
using std::cout;

constexpr long num_elements = 1e6;


void test_unordered_set() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::unordered_set<int> s;
        for (int i = 0; i < num_elements; i++)
            s.insert(i);
        cout << "unordered_set.insert(i): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            s.erase(s.find(i));
        cout << "unordered_set.erase(unordered_s.find(i)): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_unordered_map() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::unordered_map<int, int> m;
        for (int i = 0; i < num_elements; i++)
            m[i] = i;
        cout << "unordered_map[i] = i: " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            m.erase(m.find(i));
        cout << "unordered_map.erase(m.find(i)): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_set() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::set<int> s;
        for (int i = 0; i < num_elements; i++)
            s.insert(i);
        cout << "set.insert(i): " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            s.erase(s.find(i));
        cout << "set.erase(s.find(i)): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}

void test_map() {
    Timer total(num_elements);

    {
        Timer t(num_elements);

        std::map<int, int> m;
        for (int i = 0; i < num_elements; i++)
            m[i] = i;
        cout << "map[i] = i: " << t.report() << "\n";

        t.reset();

        for (int i = 0; i < num_elements; i++)
            m.erase(m.find(i));
        cout << "map.erase(m.find(i)): " << t.report() << "\n";
    }

    cout << "total: " << total.report() << "\n\n";
}


int main() {
    cout << "\n";

    test_unordered_set();
    test_unordered_map();
    test_set();
    test_map();


    return 0;
}

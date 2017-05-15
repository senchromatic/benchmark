#include <climits>
#include <cstring>
#include <iostream>
#include <string>

#include "../../lib/memory.h"
#include "../../lib/timer.h"
#include "../../lib/type.h"


using Benchmarking::CHAR_SIZE;
using Benchmarking::ll;

using Benchmarking::Memory;
using Benchmarking::Timer;

using std::cout;
using std::string;

constexpr ll LENGTH = 1e8;


void test_stl_string(const ll &base) {
    string mem;

    string s1(LENGTH, CHAR_MAX);
    string s2(LENGTH, CHAR_MAX);

    Timer total(LENGTH);
    {
        Memory memory(LENGTH, CHAR_SIZE);
        Timer timer(LENGTH);

        string s0;
        s0.resize(LENGTH);
        cout << "new stl_string[LEN]: " << timer.report(0) << '\n';

        mem = memory.report();
        timer.reset();

        for (ll i = 0; i < LENGTH; i++)
            s0[i] = i;
        cout << "stl_string[i] = c: " << timer.report(base) << '\n';

        timer.reset();

        s1 = s2;
        cout << "stl_string1 = stl_string2: " << timer.report(0) << '\n';

        --s2[LENGTH-1];
        timer.reset();

        s1 == s2;
        cout << "stl_string1 < stl_string2: " << timer.report(0) << '\n';

        timer.reset();

        s1 += s2;
        cout << "stl_string1 += stl_string2: " << timer.report(0) << '\n';
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_c_string(const ll &base) {
    string mem;

    char *s1 = new char[2*LENGTH]();
    memset(s1, CHAR_MAX, LENGTH);
    char *s2 = new char[LENGTH]();
    memset(s1, CHAR_MAX, LENGTH);

    Timer total(LENGTH);
    {
        Memory memory(LENGTH, CHAR_SIZE);
        Timer timer(LENGTH);

        char *s0 = new char[LENGTH]();
        cout << "new c_string[LEN]: " << timer.report(0) << '\n';

        mem = memory.report();
        timer.reset();

        for (ll i = 0; i < LENGTH; i++)
            s0[i] = i;
        cout << "c_string[i] = c: " << timer.report(base) << '\n';

        timer.reset();

        strcpy(s1, s2);
        cout << "c_string1 = c_string2: " << timer.report(0) << '\n';

        --s2[LENGTH-1];
        timer.reset();

        strcmp(s1, s2);
        cout << "c_string1 < c_string2: " << timer.report(0) << '\n';

        timer.reset();

        strcat(s1, s2);
        cout << "c_string1 += c_string2: " << timer.report(0) << '\n';

        delete[] s0;
    }
    cout << "total time: " << total.report(base) << '\n';

    cout << "overhead memory: " << mem << "\n\n";
    delete[] s1;
    delete[] s2;
}


int main() {
    cout << '\n';

    char c;
    Timer loop(LENGTH);
    for (ll i = 0; i < LENGTH; i++)
        c = i;
    ll base = loop.elapsed();

    test_stl_string(base);
    test_c_string(base);

    cout << '\n';
    return 0;
}

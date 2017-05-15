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


void test_stl_string() {

    Memory memory(LENGTH, CHAR_SIZE);
    string s1(LENGTH, CHAR_MAX);
    string mem = memory.report();
    --s1[LENGTH-1];

    Timer total(LENGTH);
    {
        Timer timer(LENGTH);

        string s0;
        s0.resize(LENGTH);
        cout << "new stl_string: " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < LENGTH; i++)
            s0[i] = CHAR_MAX;
        cout << "stl_string[i] = " << int(CHAR_MAX) << ": " << timer.report() << '\n';

        timer.reset();

        string s2(LENGTH, CHAR_MAX);
        cout << "new stl_string = {" << int(CHAR_MAX) << "}: " << timer.report() << '\n';

        timer.reset();

        s1 == s2;
        cout << "stl_string1 < stl_string2: " << timer.report() << '\n';

        timer.reset();

        s1 = s2;
        cout << "stl_string1 = stl_string2: " << timer.report() << '\n';

        timer.reset();

        s1 += s2;
        cout << "stl_string1 += stl_string2: " << timer.report() << '\n';
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
}

void test_c_string() {
    string mem;

    char *s1 = new char[2*LENGTH]();
    memset(s1, CHAR_MAX, LENGTH);
    --s1[LENGTH-1];

    Timer total(LENGTH);
    {
        Memory memory(LENGTH, CHAR_SIZE);
        Timer timer(LENGTH);

        char *s0 = new char[LENGTH]();
        cout << "new c_string: " << timer.report() << '\n';

        mem = memory.report();
        timer.reset();

        for (int i = 0; i < LENGTH; i++)
            s0[i] = CHAR_MAX;
        cout << "c_string[i] = " << int(CHAR_MAX) << ": " << timer.report() << '\n';

        timer.reset();

        char *s2 = new char[LENGTH]();
        memset(s2, CHAR_MAX, LENGTH);
        cout << "new c_string = {" << int(CHAR_MAX) << "}: " << timer.report() << '\n';

        timer.reset();

        int cmp = strcmp(s1, s2);
        cout << "c_string1 < c_string2: " << timer.report() << '\n';

        timer.reset();

        strcpy(s1, s2);
        cout << "c_string1 = c_string2: " << timer.report() << '\n';

        timer.reset();

        strcat(s1, s2);
        cout << "c_string1 += c_string2: " << timer.report() << '\n';

        delete[] s0;
        delete[] s2;
    }
    cout << "total time: " << total.report() << '\n';

    cout << "overhead memory: " << mem << "\n\n";
    delete[] s1;
}


int main() {
    cout << '\n';

    test_stl_string();
    test_c_string();

    return 0;
}

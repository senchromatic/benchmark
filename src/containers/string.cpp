#include <cstring>
#include <iostream>
#include <string>

#include "../../lib/timer.h"


using Benchmarking::Timer;
using std::cout;
using std::string;

constexpr long LENGTH = 1e8;
constexpr char C = 127;


void test_stl_string() {

    string s1(LENGTH, C);
    --s1[LENGTH-1];

    Timer total(LENGTH);
    {
        Timer t(LENGTH);

        string s0;
        s0.resize(LENGTH);
        cout << "new stl_string: " << t.report() << '\n';

        t.reset();

        for (int i = 0; i < LENGTH; i++)
            s0[i] = C;
        cout << "stl_string[i] = " << int(C) << ": " << t.report() << '\n';

        t.reset();

        string s2(LENGTH, C);
        cout << "new stl_string = {" << int(C) << "}: " << t.report() << '\n';

        t.reset();

        s1 == s2;
        cout << "stl_string1 < stl_string2: " << t.report() << '\n';

        t.reset();

        s1 = s2;
        cout << "stl_string1 = stl_string2: " << t.report() << '\n';

        t.reset();

        s1 += s2;
        cout << "stl_string1 += stl_string2: " << t.report() << '\n';
    }
    cout << "total: " << total.report() << "\n\n";

}

void test_c_string() {

    char *s1 = new char[2*LENGTH]();
    memset(s1, C, LENGTH);
    --s1[LENGTH-1];

    Timer total(LENGTH);
    {
        Timer t(LENGTH);

        char *s0 = new char[LENGTH]();
        cout << "new c_string: " << t.report() << '\n';

        t.reset();

        for (int i = 0; i < LENGTH; i++)
            s0[i] = C;
        cout << "c_string[i] = " << int(C) << ": " << t.report() << '\n';

        t.reset();

        char *s2 = new char[LENGTH]();
        memset(s2, C, LENGTH);
        cout << "new c_string = {" << int(C) << "}: " << t.report() << '\n';

        t.reset();

        int cmp = strcmp(s1, s2);
        cout << "c_string1 < c_string2: " << t.report() << '\n';

        t.reset();

        strcpy(s1, s2);
        cout << "c_string1 = c_string2: " << t.report() << '\n';

        t.reset();

        strcat(s1, s2);
        cout << "c_string1 += c_string2: " << t.report() << '\n';

        delete[] s0;
        delete[] s2;
    }
    cout << "total: " << total.report() << "\n\n";

    delete[] s1;
}


int main() {
    cout << '\n';

    test_stl_string();
    test_c_string();

    return 0;
}

#include <cstring>
#include <iostream>
#include <string>

#include "../../lib/timer.h"


using Benchmarking::Timer;
using std::cout;
using std::string;

constexpr long LENGTH = 1e8;
constexpr char CHARACTER = 127;


void test_stl_string() {

    string s1(LENGTH, CHARACTER);
    --s1[LENGTH-1];

    Timer total(LENGTH);
    {
        Timer timer(LENGTH);

        string s0;
        s0.resize(LENGTH);
        cout << "new stl_string: " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < LENGTH; i++)
            s0[i] = CHARACTER;
        cout << "stl_string[i] = " << int(CHARACTER) << ": " << timer.report() << '\n';

        timer.reset();

        string s2(LENGTH, CHARACTER);
        cout << "new stl_string = {" << int(CHARACTER) << "}: " << timer.report() << '\n';

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
    cout << "total: " << total.report() << "\n\n";

}

void test_c_string() {

    char *s1 = new char[2*LENGTH]();
    memset(s1, CHARACTER, LENGTH);
    --s1[LENGTH-1];

    Timer total(LENGTH);
    {
        Timer timer(LENGTH);

        char *s0 = new char[LENGTH]();
        cout << "new c_string: " << timer.report() << '\n';

        timer.reset();

        for (int i = 0; i < LENGTH; i++)
            s0[i] = CHARACTER;
        cout << "c_string[i] = " << int(CHARACTER) << ": " << timer.report() << '\n';

        timer.reset();

        char *s2 = new char[LENGTH]();
        memset(s2, CHARACTER, LENGTH);
        cout << "new c_string = {" << int(CHARACTER) << "}: " << timer.report() << '\n';

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
    cout << "total: " << total.report() << "\n\n";

    delete[] s1;
}


int main() {
    cout << '\n';

    test_stl_string();
    test_c_string();

    return 0;
}

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "../../lib/timer.h"
#include "../../lib/type.h"


using Benchmarking::ll;
using Benchmarking::Timer;

using std::rand;

constexpr ll NUM_ELEMENTS = 1e6;

ll base = 0;
std::ofstream fout("logs/common_factors.txt");


void test_stl_gcd() {
    Timer timer(NUM_ELEMENTS, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS; i++) {
        ll n1 = rand(), n2 = rand();
        std::__gcd(n1, n2);
    }
    fout << "stl::gcd(n1, n2): " << timer.report(base) << '\n';
}

inline ll euclidean_algorithm(const ll &a, const ll &b) {
    if (b == 0)
        return a;
    return euclidean_algorithm(b, a % b);
}

void test_custom_gcd() {
    Timer timer(NUM_ELEMENTS, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS; i++) {
        ll n1 = rand(), n2 = rand();
        euclidean_algorithm(std::max(n1, n2), std::min(n1, n2));
    }
    fout << "custom::gcd(n1, n2): " << timer.report(base) << '\n';
}

int main() {
    std::srand(std::time(0));
    
    Timer loop(NUM_ELEMENTS, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS; i++) {
        ll n1 = rand(), n2 = rand();
    }
    base = loop.elapsed();

    test_stl_gcd();
    test_custom_gcd();
  
    return 0;
}

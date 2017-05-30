#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>

#include "../../lib/random.h"
#include "../../lib/timer.h"
#include "../../lib/type.h"


using Benchmarking::ll;
using Benchmarking::Timer;

using Benchmarking::rand_64;
using std::__gcd;
using std::max;
using std::min;
using std::rand;

constexpr ll NUM_ELEMENTS = 1e6;
constexpr bool PARANOIA = false;

ll base = 0;
std::ofstream fout("logs/gcd.txt");


void test_stl_gcd() {
    Timer timer(NUM_ELEMENTS, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS; i++) {
        ll n1 = rand_64(), n2 = rand_64();
        __gcd(n1, n2);
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
        ll n1 = rand_64(), n2 = rand_64();
        euclidean_algorithm(max(n1, n2), min(n1, n2));
    }
    fout << "custom::gcd(n1, n2): " << timer.report(base) << '\n';
}

int main() {
    Benchmarking::random_seed();
    
    Timer loop(NUM_ELEMENTS, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS; i++) {
        ll n1 = rand_64(), n2 = rand_64();
    }
    base = loop.elapsed();

	if (PARANOIA)
		for (ll i = 0; i < NUM_ELEMENTS; i++) {
			ll n1 = rand_64(), n2 = rand_64();
			assert(__gcd(n1, n2) == euclidean_algorithm(max(n1, n2), min(n1, n2)));
		}

    test_stl_gcd();
    test_custom_gcd();
  
    return 0;
}

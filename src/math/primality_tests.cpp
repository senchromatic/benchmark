#include <cassert>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "../../lib/random.h"
#include "../../lib/timer.h"
#include "../../lib/type.h"
#include "primality_tests.h"


using Benchmarking::ll;
using Benchmarking::Timer;

using Benchmarking::odd;
using Benchmarking::trodd;

using Benchmarking::TrialDivision;

using Benchmarking::UPPER_LIMITS;
using Benchmarking::WITNESSES;
using Benchmarking::MillerRabin;

using std::rand;

constexpr ll NUM_ELEMENTS_TRIAL_DIVISION = 1e5, NUM_ELEMENTS_MILLER_RABIN = 1e6;
constexpr bool PARANOIA = false;

std::ofstream fout("logs/primality_tests.txt");


bool TrialDivision::is_prime(const ll &n) {
    if (n <= 3)
        return n >= 2;
    if (!odd(n) || !trodd(n))
        return false;
    for (ll i = 5; i*i <= n; i += 6)
        if (n % i == 0 || n % (i+2) == 0)
            return false;
    return true;
}

void test_trial_division() {
    Timer loop(NUM_ELEMENTS_TRIAL_DIVISION, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS_TRIAL_DIVISION; i++)
        rand();
    ll base = loop.elapsed();
    
    Timer timer(NUM_ELEMENTS_TRIAL_DIVISION, nullptr);
    TrialDivision tester;
    for (ll i = 0; i < NUM_ELEMENTS_TRIAL_DIVISION; i++)
        tester.is_prime(rand());
    fout << "Trial division: " << timer.report(base) << '\n';
}

bool MillerRabin::is_prime(const ll &n) {
    if ((!odd(n) && n != 2) || (n < 2) || (!trodd(n) && n != 3))
        return false;
    if (n <= 3)
        return true;
 
    ll d = n >> 1, s = 1;
    while (!odd(d)) {
        d >>= 1;
        ++s;
    }
    
    int n_limits = UPPER_LIMITS.size();
    for (int i = 0; i < n_limits; i++)
        if (n < UPPER_LIMITS[i]) {
            bool prime = true;
            const std::vector<ll> &witnesses = WITNESSES[i];
            for (int j = 0; prime && j < witnesses.size(); j++)
                prime &= witness(n, s, d, witnesses[j]);
            return prime;
        }
}

ll MillerRabin::integer_exp(const ll &a, const ll &n0, const ll &mod) {
    ll power = a, result = 1;
 
    for (ll n = n0; n; n >>= 1) {
        if (odd(n))
            result = (result * power) % mod;
        power = (power * power) % mod;
    }
    
    return result;
}

bool MillerRabin::witness(const ll &n, const ll &s0, const ll &d, const ll &a) {
    ll x = integer_exp(a, d, n), y;
 
    for (ll s = s0; s; --s) {
        y = (x * x) % n;
        if (y == 1 && x != 1 && x != n-1)
            return false;
        x = y;
    }
    return y == 1;
}

void test_miller_rabin() {
    Timer loop(NUM_ELEMENTS_MILLER_RABIN, nullptr);
    for (ll i = 0; i < NUM_ELEMENTS_MILLER_RABIN; i++)
        rand();
    ll base = loop.elapsed();
    
    Timer timer(NUM_ELEMENTS_MILLER_RABIN, nullptr);
    MillerRabin tester;
    for (ll i = 0; i < NUM_ELEMENTS_MILLER_RABIN; i++)
        tester.is_prime(rand());
    fout << "Miller-Rabin: " << timer.report(base) << '\n';
}

int main() {
    Benchmarking::random_seed();

    if (PARANOIA) {
        assert(UPPER_LIMITS.size() == WITNESSES.size());
        TrialDivision tester1;
        MillerRabin tester2;
        for (ll i = 0; i < std::min(NUM_ELEMENTS_TRIAL_DIVISION, NUM_ELEMENTS_MILLER_RABIN); i++) {
            ll n = rand();  // use 32-bit integer to avoid overflow with Miller-Rabin
            assert(tester1.is_prime(n) == tester2.is_prime(n));
        }
    }
    
    test_trial_division();
    test_miller_rabin();
    
    return 0;
}

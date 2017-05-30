#ifndef PRIMALITY_TESTS_H
#define PRIMALITY_TESTS_H


#include <climits>
#include <vector>


namespace Benchmarking {
    
    inline bool odd(const ll &n) {
        return n & 1;
    }

    inline bool trodd(const ll &n) {
        return n % 3;
    }
    
    class TrialDivision {
    public:
        static bool is_prime(const ll &n);
    };
    
    void test_trial_division();
    
    const std::vector<Benchmarking::ll> UPPER_LIMITS {
        2047,
        1373653,
        9080191,
        25326001,
        3215031751,
        4759123141,
        1122004669633,
        2152302898747,
        3474749660383,
        341550071728321,
        3825123056546413051,
        LLONG_MAX
    };
    
    const std::vector<std::vector<Benchmarking::ll>> WITNESSES {
        {2},
        {2, 3},
        {31, 73},
        {2, 3, 5},
        {2, 3, 5, 7},
        {2, 7, 61},
        {2, 13, 23, 1662803},
        {2, 3, 5, 7, 11},
        {2, 3, 5, 7, 11, 13},
        {2, 3, 5, 7, 11, 13, 17},
        {2, 3, 5, 7, 11, 13, 17, 19, 23},
        {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}
    };
    
    class MillerRabin {
    public:
        static bool is_prime(const ll &n);
    private:
        static ll integer_exp(const ll &a, const ll &n0, const ll &mod);
        static bool witness(const ll &n, const ll &s0, const ll &d, const ll &a);
    };
    
    void test_miller_rabin();
    
}


#endif // PRIMALITY_TESTS_H

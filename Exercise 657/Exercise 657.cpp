#include <iostream>
#include <primes.h>

using namespace std;
using ProjectEuler::powMod32;
using ProjectEuler::mod_inverse;

/*
 * Obtain the n'th coefficient of 1/((1 - x)(1 - b * x)), modulo p.
 */
inline uint64_t sumPowers(uint64_t b, uint64_t n, uint64_t p) {
    if (b == 0)
        return 1;
    if (b == 1)
        return (n + 1) % p;
    uint64_t res = powMod32(b, n + 1, p) - 1;
    return (res * mod_inverse(b - 1, p)) % p;
}

int main () {
    uint64_t const a = 10000000, n = 1000000000000ULL, p = 1000000007;

    /*
     * Within the loop, nu (or nu(b)) represents the coefficient
     *
     *     (-1)^(a + b + 1) (a choose b).
     */
    uint64_t sum = 0, nu = (a % 2 == 0) ? (p - 1) : (1);

    for (uint64_t b = 0; b < a; b++) {
        sum += (nu * sumPowers(b, n, p)) % p;
        if (sum >= p)
            sum -= p;

        /*
         * Update nu for the next value of b using the recursion:
         *
         *     nu(b + 1) = -(a - b)*nu(b)/(b + 1).
         */
        nu = (nu * mod_inverse(b + 1, p)) % p;
        nu = (nu * (a - b)) % p;
        nu = p - nu;
    }

    cout << sum << endl;
    return 0;
}

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

#define P_VALUE 100000000u
#define MODULUS 1000000007u
#define NBIT(s,n) (s[n >> 5] & (1 << (n & 31)))
uint32_t uint_sqrt(uint64_t);
uint32_t prime_count(uint32_t*,uint32_t,uint32_t);
uint32_t mod_prod(uint32_t*,uint32_t);
bool prime(uint32_t*,uint32_t);

int main(void)
{
    uint32_t n, sq = uint_sqrt(P_VALUE), i, d, primecount, nc;
    uint32_t* sieve;
    uint32_t* plist;
    uint32_t* ktable;
    
    // first sieve primes up to 1e8 (~6MB memory)
    sieve = (uint32_t*) calloc(sizeof(uint32_t), 1 + P_VALUE >> 6);
    for (n = 1u; n <= sq; ++n)
    {
        if (NBIT(sieve, n)) continue; // composite
        i = n, d = (i << 1) + 1u;
        while ((i += d) <= P_VALUE >> 1) // multiples 3n,5n,7n,etc
            sieve[i >> 5] |= 1 << (i & 31);
    }
    // build a list of primes
    primecount = 1u;
    for (i = 1u; i <= P_VALUE >> 1; ++i)
        if (!NBIT(sieve, i)) ++primecount;
    // allocate and store primes
    plist = (uint32_t*) malloc(sizeof(uint32_t) * primecount);
    plist[0] = 2u;
    primecount = 1u; // index for storing primes, returns to original value
    for (i = 1u; i < P_VALUE >> 1; ++i) // next store odd primes
        if (!NBIT(sieve, i))
            plist[primecount++] = (i << 1) + 1u;
    // allocate a table to count sequences for all k values
    // determine length of table as the longest prime sequence possible
    // generating the prime sequence starting at 1e8 will get that
    // start at 2 to include 1st number and last with 1 extra space
    d = 2u, nc = P_VALUE;
    while (nc != 1u)
    {
        nc = prime_count(plist, primecount, nc);
        ++d;
    }
    ktable = (uint32_t*) calloc(sizeof(uint32_t), i);
    // loop for all starting values, assuming all pi sequences end in 1
    for (n = P_VALUE; n != 1u; --n)
    {
        nc = n;
        i = 0u; // count nonprimes
        if (!prime(sieve, nc)) ++i;
        // get sequence to length of 2
        nc = prime_count(plist, primecount, nc);
        if (!prime(sieve, nc)) ++i;
        // sequence is length of 2 so start counting pi sequences
        ++ktable[i];
        while (nc != 1u) // continue until end of pi sequence
        {
            nc = prime_count(plist, primecount, nc);
            if (!prime(sieve, nc)) ++i;
            ++ktable[i];
        }
    }
    printf("sieve, all starting nums: %u\n", mod_prod(ktable, d));
    
    free(sieve);
    free(plist);
    free(ktable);
    return 0;
}

// prime function made specifically for this problem
bool prime(uint32_t* sieve, uint32_t n)
{
    if (n < 2u) return 0; // 0,1
    if (n == 2u) return 1;
    if (!(n % 2u)) return 0; // even, not in sieve
    // odd, at least 3, in sieve
    return !NBIT(sieve, n >> 1);
}

// returns the product of all integers mod modulus (skips zeros)
uint32_t mod_prod(uint32_t* list, uint32_t len)
{
    uint64_t prodmod = 1u;
    uint32_t i;
    for (i = 0u; i != len; ++i)
        if (list[i])
        {
            prodmod *= list[i];
            prodmod %= MODULUS;
        }
    return prodmod;
}

// returns number of primes not exceeding n
// DO NOT PASS n < 2 or it may crash
uint32_t prime_count(uint32_t* list, uint32_t pc, uint32_t n)
{
    // find first value exceeding n and return its index
    uint32_t l = 0u, mid;
    //--pc;
    while (l < pc)
    {
        mid = (l + pc) >> 1;
        if (list[mid] <= n)
        {
            l = mid + 1u;
            if (list[l] > n) return l;
        }
        else // list[mid] > n
        {
            pc = mid - 1u;
            if (list[pc] <= n) return mid;
        }
    }
}

uint32_t uint_sqrt(uint64_t n) // floor(sqrt(n))
{
    uint64_t sq = 0uL, one = 0x4000000000000000uL;
    while (one > n) one >>= 2;
    while (one)
    {
        if (n >= sq + one)
        {
            n -= (sq + one);
            sq += (one << 1);
        }
        sq >>= 1;
        one >>= 2;
    }
    return (uint32_t) sq;
}

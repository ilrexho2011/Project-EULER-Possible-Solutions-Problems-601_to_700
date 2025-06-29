#include <inttypes.h>
#include <math.h>
#include <stdio.h>

#include <primesieve.h>

#define MAX 10000000000

uint32_t *the_primes;
size_t the_number_of_primes;
uint32_t the_number_of_srs_numbers = 1;

void r(uint64_t product, int32_t numfacts, int32_t pindex, int64_t maxfact) {
  if (the_number_of_primes == pindex) {
    if (1 < numfacts && maxfact * maxfact < product) {
      ++the_number_of_srs_numbers;
    }
    return;
  }

  r(product, numfacts, pindex + 1, maxfact);

  uint64_t p = the_primes[pindex];

  if (maxfact < p) {
    maxfact = p;
  }

  for (;;) {
    product *= p;
    ++numfacts;

    if (MAX < product) {
      return;
    }

    r(product, numfacts, pindex + 1, maxfact);
  }
}

int main() {
  the_primes = primesieve_generate_primes(0, sqrt(MAX), &the_number_of_primes,
                                          UINT32_PRIMES);

  r(1, 0, 0, 1);

  printf("%" PRIu32 "\n", the_number_of_srs_numbers);
}
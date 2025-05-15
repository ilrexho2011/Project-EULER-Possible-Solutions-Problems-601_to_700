#include <bits/stdc++.h>

using namespace std;

const int MaxSieve = 5e8 + 100;

bool is_prime[MaxSieve];
long long N;
long long answer = 1;

void Bt(const long long rem, int prime, bool parity) {
  while (true) {
    while (!is_prime[prime]) { ++prime; }

    if (!parity) {
      if ((long long)prime * prime > rem) { return; }
    } else {
      if ((long long)prime * prime > rem / prime) { return; }
    }

    long long nrem = rem / prime;

    for (int k = 1; nrem; ++k) {
      if (k % 3 != 1) {
        const bool next_parity = parity ^ (k % 3 == 2);
        if (next_parity && k)
          ++answer;
        Bt(nrem, prime + 1, next_parity);
      }

      nrem /= prime;
    }

    ++prime;
  }
}

int main() {
  fill_n(is_prime, MaxSieve, true);
  for (int p = 2; p * p < MaxSieve; ++p) {
    if (!is_prime[p]) { continue; }
    for (int i = p * p; i < MaxSieve; i += p)
      is_prime[i] = false;
  }

  cin >> N;
  Bt(N, 2, true);

  cout << answer << "\n";
}
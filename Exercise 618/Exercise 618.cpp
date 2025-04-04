#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 1e5;
const int mod = 1e9;

int main(int argc, char const *argv[]) {
  ll ans = 0;
  std::vector<ll> fib(26,0);
  fib[1] = fib[2] = 1;
  for(int i = 3;i <= 25;i++) {
    fib[i] = fib[i-1] + fib[i-2];
  }
  std::vector<int> isprime(1e5+123,1);
  std::vector<ll> dp(1e5,0);
  isprime[0] = 0;
  isprime[1] = 0;
  isprime[2] = 1;
  for(int i=2;i<maxn;i++) {
    if(isprime[i]) {
      for(int j= i+i;j<maxn;j+=i) {
        isprime[j] = 0;
      }
    }
  }

  int id = 0;
  std::vector<int> primes(1e5);
  for(int i = 2;i < 1e5;i++) {
    if(isprime[i]==1) {
      primes[id++] = i;
    }
  }

  std::cout << "init finish" << '\n';

  dp[0] = 1;
  for(int x:primes) {
    if(x > fib[25]) {
      break;
    }
    for(int j = x; j <= fib[25]; j++) {
      dp[j] = (dp[j] + dp[j - x] * x) % mod;
      dp[j] %= mod;
    }
   }
  for(int i=2;i<=24;i++) {
    ans += dp[fib[i]];
    ans %= mod;
 }
  std::cout << ans % mod << '\n';
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
  return 0;
}

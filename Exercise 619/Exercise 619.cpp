#include <bits/stdc++.h>

using namespace std;
typedef long long ll;
const int maxn = 2e6+100;
const int mod = 1e9+7;

//O(logb)
long long qpower(long long a,long long b,long long mod)
{
    long long ans=1;
    while(b>0)
    {
        if(b&1)
            ans=(ans*a)%mod;
        b>>=1;
        a=(a*a)%mod;
    }
    return ans;
}

ll A=1000000;
ll B=1234567;

int main(int argc, char const *argv[]) {
  ll cnt = 0;
  ll ans = 0;
  std::vector<int> isprime(2e6+123,1);
  isprime[0] = 0;
  isprime[1] = 0;
  isprime[2] = 1;
  for(size_t i = 2;i < maxn;i++) {
    if(isprime[i]) {
      for(size_t j = i + i;j < maxn;j += i) {
        isprime[j] = 0;
      }
    }
  }
  std::cout << "init finish" << '\n';
  for(size_t i = 2; i <= B;i++) {
    if(isprime[i]) {
      if(floor((A - 1) / i) != floor( B / i )) {
        cnt++;
      }
    }
  }
  ans = qpower(2,(B-A+1)-cnt,mod);
  std::cout << (ans - 1) % mod << '\n';
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
  return 0;
}
#include <bits/stdc++.h>

using namespace std;

#define all(x) (x).begin(), (x).end()
typedef long double ld;
typedef long long ll;

const int M = 100100000;

const int mod = 1e9 + 7;

int add(int x) {  
  return x;
}

template<typename... T>
int add(int x, T... y) {  
  x += add(y...);
  if (x >= mod)
        x -= mod;
  return x;
}

template<typename... T>
int udd(int &x, T... y) { 
  return x = add(x, y...);
}

template<typename... T>
int sub(int x, T... y) { 
  return add(x, mod - add(y...));
}

int mul(int x) { 
  return x;
}

template<typename... T>
int mul(int x, T... y) { 
  return 1ll * x * mul(y...) % mod;
}

int bin(int x, int to) { 
  int y = 1;
  while (to) { 
        if (to & 1)
                  y = mul(x, y);
            x = mul(x, x);
                to >>= 1;
  }
  return y;
}

int inv(int x) { 
  assert(x != 0);
  return bin(x, mod - 2);
}

int norm(ll x) {
  x %= mod;
  if (x < 0)
    x += mod;
  return x;
}
 
int u[M];
int r[M];

const int N = 100;
int fact[N], ifact[N];

void pre() {
  fact[0] = 1;
  for (int i = 1; i < N; ++i)
    fact[i] = mul(fact[i - 1], i);
  for (int i = 0; i < N; ++i)
    ifact[i] = inv(fact[i]);
}

int binom(int n, int k) {
  if (n < 0 || k < 0 || n < k) assert("bad binom");
  return mul(fact[n], ifact[n - k], ifact[k]);
}

void sito() {
  for (int i = 2; i < M; ++i)
    if (!u[i])
      for (int j = i; j < M; j += i)
        u[j] = i;

  r[1] = 0;
  for (int i = 2; i < M; ++i) {
    int to = i / u[i];
    if (u[to] == u[i] || r[to] == -1) 
      r[i] = -1;
    else 
      r[i] = 1 + r[to];
  }
}

int fun(ll n, int k) {
  int ans = 0;
  for (ll i = 1; i < M; ++i)
    if (r[i] != -1 && r[i] >= k) {
      ll cur = (n / (i * i));
      udd(ans, mul(norm(cur), bin(mod - 1, r[i] - k), binom(r[i], k)));
    }
  return ans;
}

int main() {
#ifdef LOCAL
  assert(freopen("632.in", "r", stdin));
#endif

  ios_base::sync_with_stdio(false);

  sito();
  pre();

  ll n;
  cin >> n;
  int ans = 1;
  for (int k = 0; k < 100; ++k) {
    int x = fun(n, k);
    cout << k << ": " << x << "\n";
    if (x != 0)
      ans = mul(ans, x);
  }
  cout << ans << "\n";
}
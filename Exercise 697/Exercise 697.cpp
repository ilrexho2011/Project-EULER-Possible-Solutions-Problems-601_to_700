#include <bits/stdc++.h>
using namespace std;

using f64 = long double;

int main() {
  int N = 10'000'000;
  
  auto cdf = [&](f64 x) -> f64 {
    if (x > 0) return 1;
    f64 rv = 0, e = x;
    for (int i = 1; i < N; i++) {
      e += logl(-x) - logl(i);
      rv += expl(e);
    }
    return rv;
  };
  auto f = [&](f64 x) -> f64 {
    return cdf(-x * logl(10));
  };
  
  cout << setprecision(3) << fixed;
  f64 l = 0, r = N;
  for (int i = 0; i < 64; i++) {
    f64 m = (l + r) / 2;
    f(m) <= 0.25 ? r = m : l = m;
    cout << l << ' ' << r << '\n';
  }
  cout << l;
}
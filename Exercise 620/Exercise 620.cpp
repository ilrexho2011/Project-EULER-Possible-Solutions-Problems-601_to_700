#pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize ("O3")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,int> pii;
typedef vector<int> vi;
const int maxn = 1e6+5;
const int mod = 1e9+7;
const ll INF = 2e15;
const double PI = acos(-1.0);
#define lson x << 1, l, mid
#define rson x << 1 | 1, mid + 1, r
const int lowbit(int x) { return x&-x; }
#define in freopen("in.txt","r",stdin)
std::map<int, int> mp;

double g(int spq,int s,int p,int q)
{
  double k = 1.0 * (p + q) - 2.0 * PI;
  // std::cout << "k=" << k << '\n';
  double k1 = 1.0 * ( (s + q) * (s + q) + (s + p) * (s + p) - k * k ) / (2.0 * (s + q) * (s + p));
  // std::cout << "k1 = " << k1 << '\n';
  double k2 = 1.0 * ((s + q) * (s + q) + k * k - (s + p) * (s + p) ) / (2.0 * k * (s + q));
  // std::cout << "k2=" << k2 << '\n';
  double k3 = acos(k1);
  // std::cout << "k3=" << k3 << '\n';
  double k4 = acos(k2);
  // std::cout << "k4=" << k4 << '\n';
  double k5 = s * (k3 + k4) / PI;
  double k6 =  k4 * spq / PI;
  double k7 = p * (0.5 - k3 / (2.0 * PI));
  double res = 2.0 * k7 - k6 - k5;
  double ans = p - res;
  // std::cout << "ans=" << ans << '\n';
  return (int)ans;
}
int G(int n)
{
  int ans = 0;
  for(int s = 5;s <= n; s++) {
    for(int p = 5 ;p <= n - s; p++) {
      for(int q = p + 1; p < q && s + p + q <= n; q++) {
          ans += g(s + p + q , s , p, q);
      }
    }
  }
  return ans;
}
int main(int argc, char const *argv[]) {
  if(g(16,5,5,6) != 9) {
    std::cout << "fuck!" << '\n';
    exit(0);
  }
  else {
    std::cout << "OK...g(16,5,5,6) = 9" << '\n';
  }
  std::cout << G(16) << '\n';
  std::cout << G(20) << '\n';
  std::cout << G(500) << '\n';
  cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
  return 0;
}
#include <pe.hpp>
struct Pt{
  map<int, int> vec;
  double logv;
  int operator < (const Pt& o) const {
    return logv < o.logv;
  }
};

const int N = 23500;
const int64 mod = 123454321;
double pre[N];
const int64 target = 1000000;
Pt data[10000000];
int top;
void dfs(const Pt& last, int pos, int left, double my, double limit) {
  if (pos == 0) {
    if (my + pre[0] * left > limit) return;
    data[top] = last;
    data[top].vec[0] = left;
    data[top].logv = my + pre[0] * left;
    ++top;
    return;
  }
  for (int i = 1; i <= left; ++i) {
    double t = my + pre[pos] * i + pre[0] * (left - i);
    if (t > limit) break;
    Pt orz = last;
    orz.vec[pos] = i;
    orz.logv = t;
    for (int j = 0; j < pos; ++j)
    dfs(orz, j, left - i, my + pre[pos] * i, limit);
  }
}
int64 gen(int min2, int max2) {
  top = 0;
  for (int ttt = min2; ttt <= max2; ++ttt) {
    for (int i = 0; i < N; ++i) {
      Pt now;
      dfs(now, i, ttt, 0, max2 * pre[0]);
    }
  }
  return top;
}
int main() {
  INIT_MAXP(1000000);
  init_primes();
  cout << 17 * log(2) << endl;
  cout << log(plist[N-1]) - log(2) << endl;
  dbg(N);
  for (int i = 0; i < N; ++i)
    pre[i] = log(plist[i]);

  gen(target, target + 17);
  sort(data, data+top);
  int64 ans = 1;
  auto& who = data[target-1];
  for (int i = 0; i < N; ++i) if (who.vec[i] > 0) {
    ans = ans * power_mod(plist[i], who.vec[i], mod) % mod;
  }
  dbg(ans);

  return 0;
}
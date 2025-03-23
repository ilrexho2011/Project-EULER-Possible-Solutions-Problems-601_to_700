const int maxp = 10000000;
#include <pe>

const int F = 200;
const int64 N = 1000000000000;
const int64 sqrtN = sqrt(N);
const int64 mod = 1000000000+7;
int L;
int64 value = 1;

int64 invs[1000000 + 100];

int64 pc[250];
int64 pc1[250];

int64 ss[1000000 + 100];
int64 ls[1000000 + 100];

int64 compute(int64 n)
{
  int64 r = 0;
  for (int64 i = 1; i <= n;)
  {
    int64 v = n / i;
    int64 maxi = n / v;
    r = add_mod(r, (maxi-i+1) % mod * v % mod, mod);
    i = maxi + 1;
  }
  return r;
}
void init()
{
  for (int64 i = 1; i <= sqrtN; ++i)
  {
    ss[i] = compute(i);
    ls[i] = compute(N/i);
  }
}

int64 cal2(int64 d)
{
  int64 dd = N / d;
  if (dd <= sqrtN) return ss[dd];
  else return ls[N/dd];
}
int64 ckd;
int64 ans;
void dfs(int limit, int64 v1, int64 value, int64 miu)
{
  ++ckd;
  int64 v2 = cal2(value);
  int64 t = v1 * v2 % mod;
  if (miu > 0) ans = add_mod(ans, t, mod);
  else ans = sub_mod(ans, t, mod);
  for (int i = 0; i < limit; ++i)
  {
    const int64 p = plist[i];
    if (p > N / value) break;
    int64 t = pc[p] - 1;
    t = (t + 1) * (t + 2) / 2;
    dfs(i, v1 * invs[pc1[p]] % mod * t % mod, value * p, -miu);
  }
}
int main()
{
  init_primes(1, 1);
  init_inv(invs, 1000000, mod);
  init();
  cerr << "init finished" << endl;
  while (plist[L] <= F) ++L;
  for (int i = 0; plist[i] <= F; ++i)
  {
    const int64 p = plist[i];
    int64 c = 0;
    for (int64 t = F / p; t > 0; t /= p) c += t;
    pc[p] = c;
    pc1[p] = (c + 1) * (c + 2) / 2;
    value = value * pc1[p] % mod;
  }
  dfs(L, value, 1, 1);
  dbg(ans);
  dbg(ckd);
  return 0;
}
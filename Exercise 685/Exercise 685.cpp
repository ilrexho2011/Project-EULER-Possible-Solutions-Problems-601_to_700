#include <pe.hpp>

#define int64 int128
const int64 mod = 1000000007;
const int64 inv10 = inv_of(10, mod);
using MT = NMod64<mod>;

SL int64 cmb(int64 n, int64 m) {
  if (m > n || m < 0) return 0;
  if (m + m > n) m = n - m;
  int64 ret = 1;
  for (int64 i = n - m + 1, j = 1; i <= n; ++i, ++j) {
    ret *= i;
    ret /= j;
  }
  return ret;
}

SL int64 get_pre(int64 n) {
  auto orz = power_mod(
              [](auto& m, auto& v) {
                m(0, 0) = 10;
                m(0, 1) = 1;
                m(1, 0) = 0;
                m(1, 1) = 1;
                v[0] = 0;
                v[1] = 9;
              },
              2, n, mod);
  return orz[0];
}

SL int64 find_kth(int64 n, int64 weight, int64 now, int64 dec, int64 k) {
  for (;;) {
    if (dec == 0) {
      assert(k == 1);
      return now;
    }
    if (n == 1) {
      assert(k == 1);
      return sub_mod(now, dec * weight % mod, mod);
    }
    if (dec == 1) {
      return sub_mod(now, weight * power_mod(inv10, k-1, mod) % mod, mod);
    }

    for (int64 i = dec; i >= 0; --i) {
      const int64 total = cmb(n-1+dec-i-1, dec-i);
      if (total < k) {
        k -= total;
      } else {
        now = sub_mod(now, i * weight % mod, mod);
        weight = weight * inv10 % mod;
        dec -= i;
        --n;
        break;
      }
    }
  }
}

int64 maxneed;
SL int64 find_kth(int64 s, int64 k) {
  const int64 l = s / 9;
  int64 r = s % 9;
  for (int64 i = r; ;++i) {
    int64 ds = 0;
    for (int64 j = i; j; j /= 10) ds += j % 10;
    if (ds < r) continue;
    const int64 need = ds - r;
    cmax(maxneed, need);
    const int64 me = cmb(l + need - 1, need);
    if (me >= k) {
      int64 ret = power_mod(10, l, mod) * i % mod;
      ret += find_kth(l, power_mod(10, l-1, mod), get_pre(l), need, k);
      return ret % mod;
    }
    k -= me;
  }
  assert(0);
}

int main() {
  MT result = 7128;
  for (int64 n = 4; n <= 10000; ++n) {
    int64 tmp = find_kth(n*n*n, n*n*n*n);
    result += tmp;
  }
  dbg(result);
  return 0;
}

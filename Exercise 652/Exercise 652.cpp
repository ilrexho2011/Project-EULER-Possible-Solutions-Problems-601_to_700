#include <pe.hpp>
const int64 mod = 1000000000;

int128 solve0(int64 n, int c = 0) {
  int128 ret = 0;
  int128 cases = 0;
  for (int64 e = 1; e <= 64; ++e)
    for (int64 f = e + 1; f <= 64; ++f)
      if (gcd(e, f) == 1) {
        int128 root = nrooti(n, f);
        if (root >= 2) {
          ret += root - 2;
          ++cases;
        }
      }
  return ret + cases * c;
}

int128 solve1(int64 n) {
  int128 ret = 0;
  for (int64 e = 2; e <= 64; ++e) if (cal_mu(e) != 0) {
    int128 root = nrooti(n, e);
    if (root >= 2) {
      int128 cnt = root - 2 + 1;
      cnt = cnt * (cnt - 1) / 2;
      if (cnt > 0) {
        ret -= cal_mu(e) * (cnt - solve0(root, 1));
      }
    }
  }
  return ret;
}

int main() {
  pe().maxPrime(2000000).init();
  const int128 n = 1000000000000000000;
  int128 cnt = (n - 1) * (n - 2) / 2;
  cnt -= solve0(n);
  cnt -= solve1(n);
  cnt = cnt * 2 + 1;
  dbg(cnt);
  dbg(cnt % mod);
  return 0;
}
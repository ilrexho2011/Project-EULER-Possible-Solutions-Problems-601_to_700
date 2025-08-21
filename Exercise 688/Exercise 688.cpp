#include <iostream>
#include <cmath>
using ull = long long;
#define P 1000000007
#define INV2 500000004
ull z(ull n) {
  ull sum = 0;
  ull lim = std::sqrt(n);
  for (int k = 1; k <= lim; ++k) {
    sum += n/k;
    sum %= P;
  }
  sum = (2 * sum - lim*lim) % P;
  while (sum < 0) sum += P;
  return sum;
}
ull S1(ull n) {
  ull ans = (z(n) - z(n/2)) % P;
  while (ans < 0) ans += P;
  return ans;
}
// Sum of the odd numbers in [a, b].
ull sumodd(ull a, ull b) {
  ull b2 = ((b+1)/2)%P;
  ull sumatb = (b2*b2) % P;
  ull a2 = (a/2)%P;
  ull sumbeforea = (a2*a2) % P;
  ull ret = sumatb - sumbeforea;
  if (ret < 0) ret += P;
  return ret;
}
ull S2(ull n) {
  ull s = sqrt(n);
  ull sum = 0;
  for (ull i = 1; i <= s; ++i) {
    ull m = n/i;
    ull mp = m % P;
    if (i & 1) sum += (((i * mp) % P) * (1 + mp)) % P;
    ull high = n/i;
    ull low = std::max(n/(i+1)+1, i + 1);
    ull cnt = high - low + 1;
    ull geo = sumodd(low, high);
    sum += geo * ((i * (i + 1)) % P);
    sum %= P;
  }
  return (sum * INV2) % P;
}
int main() {
  ull N = 1e16;
  ull ans = (((N + 1) % P) * S1(N)) % P;
  while (ans < 0) ans += P;
  ans -= S2(N);
  if (ans < 0) ans += P;
  std::cout << ans << std::endl;
}
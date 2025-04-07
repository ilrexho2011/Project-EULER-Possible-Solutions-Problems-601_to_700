#include <bits/stdc++.h>

using namespace std;

typedef long long int lli;

const int N = 10000000;
const int M = 664579;

bool x[N + 1];
int sp[N + 1];
lli prime[M + 1];

lli r2(lli n) {
	lli ret = 1LL;
	if (n <= N) {
		while (n > 0 && x[n]) {
			lli p = sp[n];
			int c = 0;
			while (n > 0 && n % p == 0) {
				n /= p;
				c++;
			}
			if (p % 4 == 3) {
				if (c % 2 != 0) {
					return 0;
				}
			} else if (p % 4 == 1) {
				ret *= (c + 1);
			}
		}
		if (n > 1) {
			if (n % 4 == 3) {
				return 0;
			} else if (n % 4 == 1) {
				ret *= 2LL;
			}
		}
	} else {
		for (int i = 0; i < M && prime[i] * prime[i] <= n; i++) {
			lli p = prime[i];
			if (n % p == 0) {
				int c = 0;
				while (n > 0 && n % p == 0) {
					n /= p;
					c++;
				}
				if (p % 4 == 3) {
					if (c % 2 != 0) {
						return 0;
					}
				} else if (p % 4 == 1) {
					ret *= (c + 1);
				}
			}
		}
		if (n > 1) {
			if (n % 4 == 3) {
				return 0;
			} else if (n % 4 == 1) {
				ret *= 2LL;
			}
		}
	}
	return 4 * ret;
}

lli r3(lli n) {
	lli ret = 0;
	for (lli i = 1; i * i <= n; i += 2) {
		ret += r2(n - i * i);
	}
	ret *= 2;
	return ret;
}

lli G(lli n) {
	lli m = 8 * n + 3;
	int lambda = 0;
	lli mcopy = m;
	while (mcopy > 0 && mcopy % 9 == 0) {
		mcopy /= 9;
		lambda++;
	}
	lli ans = 0;
	if (mcopy % 3 == 1) {
		ans = (2 * lli(pow(3, lambda)) - 1) * r3(mcopy);
	} else if (mcopy % 3 == 2) {
		ans = lli(pow(3, lambda)) * r3(mcopy);
	} else {
		ans = r3(m);
	}
	ans /= 8;
	return ans;
}

int main() {
	sp[1] = 1;
	sp[2] = 2;
	int pi = 0;
	prime[pi] = 2;
	for (int i = 4; i <= N; i += 2) {
		sp[i] = 2;
		x[i] = true;
	}
	for (int i = 3; i <= N; i += 2) {
		if (!x[i]) {
			sp[i] = i;
			pi++;
			prime[pi] = i;
			int j = i + i;
			while (j <= N) {
				x[j] = true;
				sp[j] = i;
				j += i;
			}
		}
	}
	lli n = 17526 * lli(1e9);
	lli ans = G(n);
	cout << ans << "\n";
	cout << (1.0 * clock() / CLOCKS_PER_SEC) << " seconds\n";
	return 0;
}
#include <bits/stdc++.h>
using namespace std;

#define rep(i, from, to) for (int i = from; i < (to); ++i)
#define trav(a, x) for (auto& a : x)
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll MOD = 1000000007;

ll modpow(ll a, ll e) {
	if (e == 0) return 1;
	ll x = modpow(a, e >> 1);
	x = x * x % MOD;
	if (e & 1) x = x * a % MOD;
	return x;
}

typedef vector<ll> vd;
vd interpolate(vd x, vd y, int n) {
	vd res(n), temp(n);
	rep(k,0,n-1) rep(i,k+1,n)
		y[i] = (y[i] - y[k]) % MOD * modpow(x[i] - x[k], MOD-2) % MOD;
	ll last = 0; temp[0] = 1;
	rep(k,0,n) rep(i,0,n) {
		res[i] = (res[i] + y[k] * temp[i]) % MOD;
		swap(last, temp[i]);
		temp[i] = (temp[i] - last * x[k]) % MOD;
	}
	return res;
}

int main() {
	int realN = 10'000'000;
	const int deg = 5 + 1;
	const int mo = 4 * 3 * 5 * 7;
	const int add = 5;
	vd xs(deg), ys(deg);
	rep(it,0,deg) {
		int N = realN % mo + (it + add) * mo;
		ll res = 0;
		rep(a,0,N/4+1) rep(b,0,N/5+1) rep(c,0,N/7+1) {
			// 4*a + 5*b + 7*c + 3*C <= N
			// C <= floor((N - (4*a + 5*b + 7*c)) / 3)
			int Chi = N - (4*a + 5*b + 7*c);
			if (Chi < 0) break;
			Chi /= 3;
			// 2*C >= N - (5*a + 6*b + 8*c)
			// C >= ceil((N - (5*a + 6*b + 8*c)) / 2)
			int Clo = N - (5*a + 6*b + 8*c);
			if (Clo < 0) Clo = 0;
			Clo = (Clo + 1) / 2;
			if (Clo > Chi) continue;
			res += Chi - Clo + 1;
		}
		xs[it] = N;
		ys[it] = res % MOD;
	}

	vd coef = interpolate(xs, ys, deg);
	assert(coef.back() == 0);
	cout << "Polynomial:" << endl;
	rep(i,0,deg-1) {
		cout << coef[i] << " * n^" << i << endl;
	}
	cout << endl;

	ll pw = 1;
	ll sum = 0;
	rep(i,0,deg-1) {
		sum += coef[i] * pw % MOD;
		pw = pw * realN % MOD;
	}
	sum %= MOD;
	if (sum < 0) sum += MOD;

	cout << sum << endl;
}
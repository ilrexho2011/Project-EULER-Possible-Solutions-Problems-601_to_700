#include<bits/stdc++.h>
using namespace std;

using ll = long long;
const ll mod = ll(1e9) + 7;
#define rep(i,a,b) for (int i = (a); i < (b); ++i)
#define sz(a) (int)(a).size()
#define trav(x, a) for (auto& x : a)

ll modpow(ll a, ll b) {
	ll r = 1;
	while (b) {
		if (b & 1) r = r * a % mod;
		a = a * a % mod;
		b /= 2;
	}
	return r;
}

vector<ll> BerlekampMassey(vector<ll> s) {
	int n = sz(s), L = 0, m = 0;
	vector<ll> C(n), B(n), T;
	C[0] = B[0] = 1;

	ll b = 1;
	rep(i,0,n) { ++m;
		ll d = s[i] % mod;
		rep(j,1,L+1) d = (d + C[j] * s[i - j]) % mod;
		if (!d) continue;
		T = C; ll coef = d * modpow(b, mod-2) % mod;
		rep(j,m,n) C[j] = (C[j] - coef * B[j - m]) % mod;
		if (2 * L > i) continue;
		L = i + 1 - L; B = T; b = d; m = 0;
	}

	C.resize(L + 1); C.erase(C.begin());
	trav(x, C) x = (mod - x) % mod;
	return C;
}

typedef vector<ll> Poly;
ll linearRec(Poly S, Poly tr, ll k) {
	int n = sz(S);

	auto combine = [&](Poly a, Poly b) {
		Poly res(n * 2 + 1);
		rep(i,0,n+1) rep(j,0,n+1)
			res[i + j] = (res[i + j] + a[i] * b[j]) % mod;
		for (int i = 2 * n; i > n; --i) rep(j,0,n)
			res[i - 1 - j] = (res[i - 1 - j] + res[i] * tr[j]) % mod;
		res.resize(n + 1);
		return res;
	};

	Poly pol(n + 1), e(pol);
	pol[0] = e[1] = 1;

	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}

	ll res = 0;
	rep(i,0,n) res = (res + pol[i + 1] * S[i]) % mod;
	return res;
}

ll T(ll n, ll m) {
	vector<ll> cnts(n);
	cnts[1] ++;
	vector<ll> vals;
	vals.push_back(1);
	for (ll l = 1; l <= 2 * n; l++) {
		vector<ll> ncnts(n);
		ll t = 0;
		for (ll i = n-1; i >= 1; i--) {
			t += cnts[n-i];
			t %= mod;
			ncnts[i] = t;
		}
		cnts = ncnts;
		t = 0;
		for (int i = 1; i < n; i++) {
			t += cnts[i];
			t %= mod;
		}
		vals.push_back(t);
	}

	//for (int i = 0; i < int(vals.size()); i++) { cerr << i << ' ' << vals[i] << '\n'; }
	vector<ll> rec = BerlekampMassey(vals);
	//cerr << n << ' ' << rec.size() << '\n';
	//for (int i = 0; i < int(rec.size()); i++) { cerr << i << ' ' << rec[i] << '\n'; }
	assert(rec.size() <= vals.size());
	vals.resize(rec.size());
	ll res = linearRec(vals, rec, m) % mod;
	if (res < 0) res += mod;
	//cerr << n << ' ' << m << ' ' << res << '\n';
	return res;
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	assert(T(5, 5) == 246);
	assert(T(10, 100) == 862820094);
	assert(T(100, 10) == 782136797);
	cout << T(5000, 1e12) << '\n';

	return 0;
}
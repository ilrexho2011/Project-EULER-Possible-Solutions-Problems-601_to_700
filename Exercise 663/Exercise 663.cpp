#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

template<typename T>
struct segtree {
	int n, H;
	
	vector<T> value;

	segtree<T>(int n): n(n) {
		H = 32 - __builtin_clz(2*n-1);
		value.resize(2*n);
	}

	void update(int i, T v) {
		i += n;
		value[i] = v;
		for (i /= 2; i; i /= 2) value[i] = value[2*i] + value[2*i+1];
	}
	
	T query(int i, int j) {
		i += n, j += n;
		T resl, resr;
		for (; i < j; i /= 2, j /= 2) {
			if (i & 1) resl = resl + value[i++];
			if (j & 1) resr = value[--j] + resr;
		}
		return resl + resr;
	}
};

struct node {
	ll s, l, r, i;
	node (ll x = 0): s(x), l(max(x,0LL)), r(l), i(l) { }
	node (ll s, ll l, ll r, ll i): s(s), l(l), r(r), i(i) { }
	node operator+(node n) {
		return {s + n.s, max(l, s+n.l), max(r+n.s, n.r), max(max(i, n.i), r+n.l)};
	}
};

ll S(int n, int a, int b) {
	int t1 = 0, t2 = 0, t3 = 1;
	auto t = [&]() {
		int t0 = t1;
		t1 = t2, t2 = t3, t3 = (t0+t1+t2) % n;
		return t0;
	};
	
	segtree<node> S(n);

	ll res = 0;
	for (int i = 0; i < b; i++) {
		int j = t();
		ll x = S.query(j,j+1).s;
		S.update(j, node(x + 2*t() - n + 1));
		if (i >= a) res += S.query(0,n).i;
	}
	return res;
}

int main() {
	cout << S(5,0,100) << endl;
	cout << S(14,0,100) << endl;
	cout << S(107,0,1000) << endl;
	cout << S(1e7+3,1e7,1e7+2e5) << endl;
}
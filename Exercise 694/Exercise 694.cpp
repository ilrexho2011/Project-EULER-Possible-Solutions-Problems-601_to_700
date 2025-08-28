#include <bits/stdc++.h>
#define X first
#define Y second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define ini(x, y) memset(x, y, sizeof(x))
#define endl '\n'
#define fastio cin.sync_with_stdio(false); cin.tie(nullptr)
using namespace std;

using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
const int MOD = 1e9 + 7;
const int dx[] = { -1, 0, 1, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 1, 0, -1, 1, 1, -1, -1 };

vector<int> p;
const ll lim = 1000000000000000000ll;
ll ans = lim;

void go(int idx, ll now) {
	ans += lim / now;

	for (int i = idx; i < sz(p); ++i) {
		if (lim / p[i] < now) break;

		if (i == idx) {
			go(idx, now * p[i]);
		}
		else {
			ll val = (ll)p[i] * p[i] * p[i];
			if (lim / val < now) break;
			go(i, now * val);
		}
	}
}
int main() {
	fastio;
	int sieve[1000001]{};
	for (int i = 2; i < 1000000; ++i) if (!sieve[i]) {
		p.push_back(i);
		for (ll j = (ll)i * i; j < 1000000; j += i) ++sieve[j];
	}

	for (int i = 0; i < sz(p); ++i) {
		ll val = (ll)p[i] * p[i] * p[i];
		if (lim < val) break;
		go(i, val);
	}

	cout << ans;

	return 0;
}
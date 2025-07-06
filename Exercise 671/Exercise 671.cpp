#include<bits/stdc++.h>
using namespace std;
const int MAXN = 105;
const int P = 1000004321;
typedef long long ll;
typedef long double ld;
typedef unsigned long long ull;
template <typename T> void chkmax(T &x, T y) {x = max(x, y); }
template <typename T> void chkmin(T &x, T y) {x = min(x, y); } 
template <typename T> void read(T &x) {
	x = 0; int f = 1;
	char c = getchar();
	for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
	for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
	x *= f;
}
template <typename T> void write(T x) {
	if (x < 0) x = -x, putchar('-');
	if (x > 9) write(x / 10);
	putchar(x % 10 + '0');
}
template <typename T> void writeln(T x) {
	write(x);
	puts("");
}
int power(int x, int y) {
	if (y == 0) return 1;
	int tmp = power(x, y / 2);
	if (y % 2 == 0) return 1ll * tmp * tmp % P;
	else return 1ll * tmp * tmp % P * x % P;
}
void update(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
namespace LinearSequence {
	const int MAXN = 5005;
	const int MAXLOG = 62;
	const int P = 1000004321;
	vector <int> a[MAXN];
	int cnt, delta[MAXN], fail[MAXN];
	int k, h[MAXN], now[MAXLOG][MAXN];
	int power(int x, int y) {
		if (y == 0) return 1;
		int tmp = power(x, y / 2);
		if (y % 2 == 0) return 1ll * tmp * tmp % P;
		else return 1ll * tmp * tmp % P * x % P;
	}
	void times(int *res, int *x, int *y) {
		static int tmp[MAXN];
		memset(tmp, 0, sizeof(tmp));
		for (int i = 0; i <= k - 1; i++)
		for (int j = 0; j <= k - 1; j++)
			tmp[i + j] = (tmp[i + j] + 1ll * x[i] * y[j]) % P;
		for (int i = 2 * k - 2; i >= k; i--) {
			int val = tmp[i]; tmp[i] = 0;
			for (unsigned j = 0; j < a[cnt].size(); j++)
				tmp[i - j - 1] = (tmp[i - j - 1] + 1ll * val * a[cnt][j]) % P;
		}
		memcpy(res, tmp, sizeof(tmp));
	}
	void init(int n, int *val) {
		for (int i = 0; i <= cnt; i++)
			a[i].clear();
		cnt = 0;
		for (int i = 1; i <= n; i++) {
			delta[i] = val[i];
			for (unsigned j = 0; j < a[cnt].size(); j++)
				delta[i] = (delta[i] - 1ll * a[cnt][j] * val[i - j - 1] % P + P) % P;
			if (delta[i] == 0) continue;
			fail[cnt] = i;
			if (cnt == 0) {
				a[++cnt].resize(i);
				continue;
			}
			int mul = 1ll * delta[i] * power(delta[fail[cnt - 1]], P - 2) % P;
			a[cnt + 1].resize(i - fail[cnt - 1] - 1);
			a[cnt + 1].push_back(mul);
			for (unsigned j = 0; j < a[cnt - 1].size(); j++)
				a[cnt + 1].push_back(1ll * a[cnt - 1][j] * (P - mul) % P);
			if (a[cnt + 1].size() < a[cnt].size()) a[cnt + 1].resize(a[cnt].size());
			for (unsigned j = 0; j < a[cnt].size(); j++)
				a[cnt + 1][j] = (a[cnt + 1][j] + a[cnt][j]) % P;
			cnt++;
		}
		if (n < 2 * a[cnt].size() + 5) {
			cerr << "Failed!" << endl;
			return;
		}
		memset(now, 0, sizeof(now));
		k = a[cnt].size();
		if (k == 1) now[0][0] = a[cnt][0];
		else now[0][1] = 1;
		for (int i = 1; i <= 2 * k; i++)
			h[i] = val[i];
		for (int p = 1; p < MAXLOG; p++)
			times(now[p], now[p - 1], now[p - 1]);
	}
	int query(long long n) {
		if (n <= k) return h[n]; n -= k;
		static int res[MAXN];
		memset(res, 0, sizeof(res));
		res[0] = 1;
		for (int p = 0; p < MAXLOG; p++) {
			long long tmp = 1ll << p;
			if (n & tmp) times(res, res, now[p]);
		}
		int ans = 0;
		for (int i = 0; i <= k - 1; i++)
			ans = (ans + 1ll * res[i] * h[i + k]) % P;
		return ans;
	}
}
struct State {int cola, colb, dista, distb; };
bool operator < (State a, State b) {
	if (a.cola == b.cola) {
		if (a.colb == b.colb) {
			if (a.dista == b.dista) return a.distb < b.distb;
			else return a.dista < b.dista;
		} return a.colb < b.colb;
	} return a.cola < b.cola;
}
int n, m, ans[MAXN];
map <State, int> mp[MAXN];
set <State> start;
void initstates() {
	State now = (State) {0, 0, 0, 0};
	for (int j = 1; j <= m; j++)
		if (j != now.cola && j != now.colb) {
			State res = now;
			res.dista = res.distb = 0;
			res.cola = res.colb = j;
			start.insert(res);
		}
	for (int j = 1; j <= m; j++)
	for (int dj = 1; dj <= 3; dj++)
	for (int k = 1; k <= m; k++)
	for (int dk = 1; dk <= 3; dk++)
		if (j != k) {
			State res = now;
			res.dista = dj, res.distb = dk;
			res.cola = j, res.colb = k;
			res.dista--, res.distb--;
			start.insert(res);
		}
}
int main() {
	n = 70, m = 10;
	initstates();
	int progress = 0;
	for (auto s : start) {
		for (int i = 0; i <= n; i++)
			mp[i].clear();
		mp[0][s] = 1;
		for (int i = 1; i <= n; i++)
		for (auto x : mp[i - 1]) {
			State now = x.first;
			if (now.dista == 0 && now.distb == 0) {
				for (int j = 1; j <= m; j++)
					if (j != now.cola && j != now.colb) {
						State res = now;
						res.dista = res.distb = 0;
						res.cola = res.colb = j;
						update(mp[i][res], x.second);
					}
				if (now.cola == now.colb) {
					for (int j = 1; j <= m; j++)
					for (int dj = 1; dj <= 3; dj++)
					for (int k = 1; k <= m; k++)
					for (int dk = 1; dk <= 3; dk++)
						if (j != now.cola && k != now.colb && j != k) {
							State res = now;
							res.dista = dj, res.distb = dk;
							res.cola = j, res.colb = k;
							res.dista--, res.distb--;
							update(mp[i][res], x.second);
						}
				}
			} else if (now.dista == 0) {
				for (int j = 1; j <= m; j++)
				for (int dj = 1; dj <= 3; dj++)
					if (j != now.cola && j != now.colb) {
						State res = now;
						res.dista = dj, res.cola = j;
						res.dista--, res.distb--;
						update(mp[i][res], x.second);
					}
			} else if (now.distb == 0) {
				for (int j = 1; j <= m; j++)
				for (int dj = 1; dj <= 3; dj++)
					if (j != now.cola && j != now.colb) {
						State res = now;
						res.distb = dj, res.colb = j;
						res.dista--, res.distb--;
						update(mp[i][res], x.second);
					}
			} else {
				now.dista--, now.distb--;
				update(mp[i][now], x.second);
			}
		}
		for (int i = 1; i <= n; i++)
			update(ans[i], mp[i][s]);
		cerr << "CalculationFinished " << ++progress << '/' << start.size() << endl;
	}
	LinearSequence :: init(n, ans);
	ll N = 10004003002001ll;
	int finalans = LinearSequence :: query(N);
	writeln(1ll * finalans * power(N % P, P - 2) % P);
	return 0;
}
#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e6 + 5;
const int P = 1e9 + 7;
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
__int128 ans;
int tot, prime[MAXN], f[MAXN];
void init(int n) {
	for (int i = 2; i <= n; i++) {
		if (f[i] == 0) prime[++tot] = f[i] = i;
		for (int j = 1; j <= tot && prime[j] <= f[i]; j++) {
			int tmp = prime[j] * i;
			if (tmp > n) break;
			f[tmp] = prime[j];
		}
	}
}
ll power(ll x, int y) {
	if (y == 0) return 1;
	ll tmp = power(x, y / 2);
	if (y % 2 == 0) return tmp * tmp;
	else return tmp * tmp * x;
}
int cnt, p[MAXN], e[MAXN];
void work(int pos, ll x, ll y, ll z, ll t) {
	if (pos >= cnt + 1) {
		if ((x + y + z + t) & 1) return;
		ll p = (x + y + z + t) / 2;
		if (p > x && x >= y && y >= z && z >= t) {
			ans += 2 * p;
		}
		return;
	}
	for (int i = 0; i <= e[pos]; i++)
	for (int j = 0; i + j <= e[pos]; j++)
	for (int k = 0; i + j + k <= e[pos]; k++)
		work(pos + 1, x * power(p[pos], i), y * power(p[pos], j), z * power(p[pos], k), t * power(p[pos], e[pos] - i - j - k));
}
int main() {
	int n = 1e6; init(n);
	for (int i = 1; i <= n; i++) {
		cnt = 0;
		int tmp = i;
		while (tmp != 1) {
			if (f[tmp] == p[cnt]) e[cnt] += 2;
			else p[++cnt] = f[tmp], e[cnt] = 2;
			tmp /= f[tmp];
		}
		work(1, 1, 1, 1, 1);
		if (i % 1000 == 0) cerr << i << ' ' << "Finished" << endl;
	}
	writeln(ans);
	return 0;
}
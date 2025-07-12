#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e7 + 5;
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
const int P = 1e9 + 87;
int fac[MAXN], inv[MAXN];
int power(int x, int y) {
	if (y == 0) return 1;
	int tmp = power(x, y / 2);
	if (y % 2 == 0) return 1ll * tmp * tmp % P;
	else return 1ll * tmp * tmp % P * x % P;
}
int binom(int x, int y) {
	if (y > x) return 0;
	else return 1ll * fac[x] * inv[y] % P * inv[x - y] % P;
}
int tot, prime[MAXN], f[MAXN];
void init(int n) {
	fac[0] = 1;
	for (int i = 1; i <= n; i++)
		fac[i] = 1ll * fac[i - 1] * i % P;
	inv[n] = power(fac[n], P - 2);
	for (int i = n - 1; i >= 0; i--)
		inv[i] = inv[i + 1] * (i + 1ll) % P;
	for (int i = 2; i <= n; i++) {
		if (f[i] == 0) prime[++tot] = f[i] = i;
		for (int j = 1; j <= tot && prime[j] <= f[i]; j++) {
			int tmp = prime[j] * i;
			if (tmp > n) break;
			f[tmp] = prime[j];
		}
	}
}
void update(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
int ans[MAXN], cnt[MAXN];
int func(int x) {
	return 2 * x + 1;
}
int invn(int x) {
	return 1ll * inv[x] * fac[x - 1] % P;
}
int main() {
	int n = 1e7; init(2 * n + 1);
	ans[1] = 1;
	for (int i = 2; i <= n; i++) {
		ans[i] = ans[i - 1];
		int tmp = i;
		while (tmp != 1) {
			int x = f[tmp];
			ans[i] = 1ll * ans[i] * invn(func(cnt[x])) % P;
			cnt[x]++, tmp /= x;
			ans[i] = 1ll * ans[i] * func(cnt[x]) % P;
		}
	}
	int res = 0;
	for (int i = 2; i <= n; i++)
		update(res, ans[i]);
	writeln(res);
	return 0;
}
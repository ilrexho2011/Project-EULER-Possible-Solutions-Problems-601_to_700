#include<bits/stdc++.h>
using namespace std;
const int MAXN = 2e5 + 5;
const int P = 1e9 + 7;
const int inv2 = (P + 1) / 2;
const int inv6 = (P + 1) / 6;
const int inv24 = (P + 1) / 24;
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
int r[MAXN], b[MAXN], y[MAXN], all[MAXN][5], rb[MAXN][5];
void update(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
int main() {
	int n = 10000, m = (n + 1) / 2 - 1;
	for (int i = 1; i <= m; i++) {
		// No Child
		if (i == 1) r[i] = b[i] = y[i] = 1;
		// One Child
		update(r[i], all[i - 1][1]);
		update(b[i], all[i - 1][1]);
		update(y[i], rb[i - 1][1]);
		// Two Children
		update(r[i], 1ll * all[i - 1][2] * inv2 % P);
		update(b[i], 1ll * all[i - 1][2] * inv2 % P);
		update(y[i], 1ll * rb[i - 1][2] * inv2 % P);
		if ((i - 1) % 2 == 0) {
			update(r[i], 1ll * all[(i - 1) / 2][1] * inv2 % P);
			update(b[i], 1ll * all[(i - 1) / 2][1] * inv2 % P);
			update(y[i], 1ll * rb[(i - 1) / 2][1] * inv2 % P);
		}
		// Three Children
		update(r[i], 1ll * all[i - 1][3] * inv6 % P);
		if ((i - 1) % 3 == 0)
			update(r[i], 2ll * all[(i - 1) / 3][1] * inv6 % P);
		for (int j = 1, k = i - 3; k >= 1; j++, k -= 2)
			update(r[i], 3ll * all[j][1] * all[k][1] % P * inv6 % P);
		rb[i][1] = (0ll + r[i] + b[i]) % P;
		all[i][1] = (0ll + r[i] + b[i] + y[i]) % P;
		for (int t = 2; t <= 4; t++)
		for (int j = 1; j <= i - 1; j++) {
			update(rb[i][t], 1ll * rb[j][t - 1] * rb[i - j][1] % P);
			update(all[i][t], 1ll * all[j][t - 1] * all[i - j][1] % P);
		}
	}
	for (int i = m + 1; i <= n; i++) {
		for (int t = 2; t <= 4; t++)
		for (int j = 1; j <= i - 1; j++) {
			update(rb[i][t], 1ll * rb[j][t - 1] * rb[i - j][1] % P);
			update(all[i][t], 1ll * all[j][t - 1] * all[i - j][1] % P);
		}
	}
	int ans = 0;
	// One Center
		// No Child
		if (n == 1) update(ans, 3);
		// One Child
		update(ans, all[n - 1][1]);
		update(ans, all[n - 1][1]);
		update(ans, rb[n - 1][1]);
		// Two Children
		update(ans, 1ll * all[n - 1][2] * inv2 % P);
		update(ans, 1ll * all[n - 1][2] * inv2 % P);
		update(ans, 1ll * rb[n - 1][2] * inv2 % P);
		if ((n - 1) % 2 == 0) {
			update(ans, 1ll * all[(n - 1) / 2][1] * inv2 % P);
			update(ans, 1ll * all[(n - 1) / 2][1] * inv2 % P);
			update(ans, 1ll * rb[(n - 1) / 2][1] * inv2 % P);
		}
		// Three Children
		update(ans, 1ll * all[n - 1][3] * inv6 % P);
		update(ans, 1ll * all[n - 1][3] * inv6 % P);
		update(ans, 1ll * rb[n - 1][3] * inv6 % P);
		if ((n - 1) % 3 == 0) {
			update(ans, 2ll * all[(n - 1) / 3][1] * inv6 % P);
			update(ans, 2ll * all[(n - 1) / 3][1] * inv6 % P);
			update(ans, 2ll * rb[(n - 1) / 3][1] * inv6 % P);
		}
		for (int j = 1, k = n - 3; k >= 1; j++, k -= 2) {
			update(ans, 3ll * all[j][1] * all[k][1] % P * inv6 % P);
			update(ans, 3ll * all[j][1] * all[k][1] % P * inv6 % P);
			update(ans, 3ll * rb[j][1] * rb[k][1] % P * inv6 % P);
		}
		// Four Children
		update(ans, 1ll * all[n - 1][4] * inv24 % P);
		if ((n - 1) % 4 == 0) update(ans, 6ll * all[(n - 1) / 4][1] * inv24 % P);
		for (int j = 1, k = n - 4; k >= 1; j++, k -= 3)
			update(ans, 8ll * all[j][1] * all[k][1] % P * inv24 % P);
		if ((n - 1) % 2 == 0) {
			for (int j = 1, k = (n - 1) / 2 - 1; k >= 1; j++, k--)
				update(ans, 3ll * all[j][1] * all[k][1] % P * inv24 % P);
		}
		for (int j = 1, k = n - 3; k >= 1; j++, k -= 2)
			update(ans, 6ll * all[j][1] * all[k][2] % P * inv24 % P);
	// Two Centers
	if (n % 2 == 0) {
		int i = n / 2;
		// No Child
		if (i == 1) r[i] = b[i] = y[i] = 1;
		// One Child
		update(r[i], all[i - 1][1]);
		update(b[i], all[i - 1][1]);
		update(y[i], rb[i - 1][1]);
		// Two Children
		update(r[i], 1ll * all[i - 1][2] * inv2 % P);
		update(b[i], 1ll * all[i - 1][2] * inv2 % P);
		update(y[i], 1ll * rb[i - 1][2] * inv2 % P);
		if ((i - 1) % 2 == 0) {
			update(r[i], 1ll * all[(i - 1) / 2][1] * inv2 % P);
			update(b[i], 1ll * all[(i - 1) / 2][1] * inv2 % P);
			update(y[i], 1ll * rb[(i - 1) / 2][1] * inv2 % P);
		}
		// Three Children
		update(r[i], 1ll * all[i - 1][3] * inv6 % P);
		if ((i - 1) % 3 == 0)
			update(r[i], 2ll * all[(i - 1) / 3][1] * inv6 % P);
		for (int j = 1, k = i - 3; k >= 1; j++, k -= 2)
			update(r[i], 3ll * all[j][1] * all[k][1] % P * inv6 % P);
		int all = (0ll + r[i] + b[i] + y[i]) % P, rb = (0ll + r[i] + b[i]) % P;
		int now = (1ll * all * r[i] + 1ll * all * b[i] + 1ll * y[i] * rb + b[i] + r[i]) % P;
		update(ans, 1ll * now * inv2 % P);
	}
	writeln(ans);
	return 0;
}
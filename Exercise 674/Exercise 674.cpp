#include<bits/stdc++.h>
using namespace std;
const int MAXN = 205;
const int MAXS = 1e4 + 5;
const int P = 1e9;
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
void update(int &x, int y) {
	x += y;
	if (x >= P) x -= P;
}
const int MAXM = 5e5 + 5;
int tot, f[MAXM], lc[MAXM], rc[MAXM], value[MAXM];
char s[MAXN][MAXS];
int build(char *s, int l, int r) {
	if (r - l == 0) return s[l] - 'a' + 1;
	if (r - l == 1) return s[r] - 'a' + 1 + 26 * (s[l] - 'a' + 1);
	if (r - l == 2) return s[r] - 'a' + 1 + 26 * (s[r - 1] - 'a' + 1) + 26 * 27 * (s[l] - 'a' + 1);
	assert(s[l] == 'I' && s[l + 1] == '(' && s[r] == ')');
	l += 2, r -= 1;
	int now = 0, mid = 0;
	for (int i = l; i <= r; i++)
		if (s[i] == '(') now++;
		else if (s[i] == ')') now--;
		else if (s[i] == ',' && now == 0) assert(mid == 0), mid = i;
	int pos = ++tot;
	f[pos] = pos;
	lc[pos] = build(s, l, mid - 1);
	rc[pos] = build(s, mid + 1, r);
	return pos;
}
int F(int x) {
	if (f[x] == x) return x;
	else return f[x] = F(f[x]);
}
void dfs(int a, int b) {
	if (lc[F(a)] && lc[F(b)] == 0) swap(a, b);
	if (F(a) != F(b)) {
		int x = F(a), y = F(b);
		f[F(a)] = F(b);
		dfs(x, y);
	}
	if (lc[a] == 0 || lc[b] == 0) return;
	dfs(lc[a], lc[b]);
	dfs(rc[a], rc[b]);
}
int func(int x, int y) {
	return (1ll * (x + y + 1) * (x + y + 1) - x + y + P) % P;
}
int d[MAXM];
vector <int> a[MAXM];
int getans(char *s, char *t) {
	tot = 26 * 27 * 27;
	for (int i = 1; i <= tot; i++)
		f[i] = i, lc[i] = rc[i] = 0;
	int rs = build(s, 1, strlen(s + 1));
	int rt = build(t, 1, strlen(t + 1));
	dfs(rs, rt);
	for (int i = 1; i <= tot; i++) {
		d[i] = value[i] = 0;
		a[i].clear();
	}
	for (int i = 26 * 27 * 27 + 1; i <= tot; i++) {
		d[F(i)] += 2;
		a[F(lc[i])].push_back(F(i));
		a[F(rc[i])].push_back(F(i));
	}
	deque <int> q;
	for (int i = 1; i <= tot; i++) {
		if (F(i) == i && d[i] == 0) q.push_back(i);
		if (F(i) != i) value[i] = -1;
	}
	while (!q.empty()) {
		int tmp = q.front();
		q.pop_front();
		if (lc[tmp] == 0) value[tmp] = 0;
		else value[tmp] = func(value[F(lc[tmp])], value[F(rc[tmp])]);
		for (auto x : a[tmp])
			if (--d[x] == 0) {
				q.push_back(x);
			}
	}
	for (int i = 1; i <= tot; i++)
		if (d[i] != 0) return 0;
	return value[F(rs)];
}
int main() {
	freopen("problem.in", "r", stdin);
	int n = 149, ans = 0;
	for (int i = 1; i <= n; i++)
		scanf("\n%s", s[i] + 1);
	for (int i = 1; i <= n; i++) {
		for (int j = 1; j <= i - 1; j++) {
			update(ans, getans(s[i], s[j]));
		}
		cerr << i << '/' << 149 << " Finished" << endl;
	}
	writeln(ans);
	return 0;
}
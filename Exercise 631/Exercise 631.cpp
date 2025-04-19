#include <iostream>
#include <algorithm>

using namespace std;

const int MOD = (int)1e9 + 7;
const long long N = 49;//(int)1e18 % MOD;
const int M = 40;

bool v[N];
long long ans = 0;

void dfs(int n, int inv, int lst, int fst, int snd, int mi) {
	if (inv != lst)
		ans += N - mi;
	if (inv >= M)
		return;
	for (int i = 0, cnt = 0; i < N; i++) {
		if (v[i])
			continue;
		v[i] = true;
		int ff = i, ss = -1;
		if (fst != -1 && fst < i) ff = fst;
		if (fst != -1 && fst < i) ss = i;
		if (ss == -1 || snd != -1 && snd < ss) ss = snd;

		dfs(n + 1, inv + cnt, inv, ff, ss, max(i, mi));

		v[i] = false;
		cnt++;
		if (cnt + inv > M || snd != -1 && i > snd)
			break;
	}
}

int main() {
	dfs(0, 0, -1, -1, -1, -1);
	ans = ((ans % MOD) + MOD) % MOD;
	cout << ans << endl;
	getchar();
}
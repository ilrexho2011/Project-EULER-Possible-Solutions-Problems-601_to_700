#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>

using namespace std;

typedef long long ll;
typedef pair<int,int> PP;

/*
    freopen("input","r",stdin);
    freopen("output","w",stdout);
*/

const ll N = 1E7;
const ll M = 4E6;
const ll sz = M + 10;
const ll S = N + 10;

ll F[S], I[S];

ll P[sz], Q[sz];

ll MOD = 1E9 + 7;

ll power(ll a, ll b) {
	ll res = 1;
	while (b > 0) {
		if (b % 2) {
			res *= a;
			res %= MOD;
		}
		a *= a;
		a %= MOD;
		b /= 2;
	}
	return res;
}

void init() {
	memset(F, 0, sizeof(F));
	F[0] = 1;
	for (ll i = 1;i <= N + 1;i++) {
		F[i] = F[i - 1] * i;
		F[i] %= MOD;
	}
	I[N + 1] = power(F[N + 1], MOD - 2);
	for (ll i = N;i >= 0;i--) {
		I[i] = I[i + 1] * (i + 1);
		I[i] %= MOD;
	}
	return;
}

ll nchoosek(ll a, ll b) {
	ll base = I[b] * I[a - b];
	base %= MOD;
	return (F[a] * base) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    init();
    memset(P, 0, sizeof(P));
    memset(Q, 0, sizeof(Q));
    for (int i = 0;i <= M;i++) {
    	P[i] = power(i, N);
    }
    for (int i = 0;i <= M;i++) {
    	Q[i] = nchoosek(N + 1, i);
    	if (i % 2) Q[i] = MOD - Q[i];
    }
    ll res = 0;
    for (int i = 0;i <= M;i++) {
    	res += (Q[i] * P[M - i]) % MOD;
    	res %= MOD;
    }
    cout << res << endl;
    return 0;
}
#include "lib.h"

const ll mod = 1e9;

typedef array<array<int, 8>, 8> mat8;
// multiply matrices:
mat8 operator*(mat8 a, mat8 b) {
	mat8 c = {};
	REP(i, 8) REP(j, 8) REP(k, 8)
		c[i][k] = (c[i][k] + 1LL * a[i][j] * b[j][k]) % mod;
	return c;
}
// fast power of a matrix:
mat8 powmod(mat8 b, ll e) {
	mat8 r = {};
	REP(i, 8) r[i][i] = 1;
	for (; e; e /= 2, b = b*b)
		if (e & 1) r = r * b;
	return r;
}
// counts the r[x] = #{ i \in {0, \dots, N-1} : SG[i] = x }.
array<int, 8> sg_counts(ll N) {
	// periodicity: (0 0 1 1 2 2 3 3 4) (0 0 1 1 2 2 3 3 4) ...
	array<int, 8> r = {};
	int q = N / 9, m = N % 9, j = 0; // j is a loop-counter
	for (int i : { 2, 2, 2, 2, 1 }) r[j++] += q * i;
	j = 0;
	for (int i : { 0, 0, 1, 1, 2, 2, 3, 3, 4 }) {
		if (j++ >= m) break;
		r[i]++;
	}

	return r;
}

int main() {
	ll N, C;
	cin >> N >> C;

	auto nr_sg = sg_counts(N);
	mat8 T = {};
	REP(i, 8) REP(j, 8) T[i][j] = nr_sg[i^j];

	mat8 B = powmod(T, 2*C);
	ll ret2 = 0;
	rep(i, 1, 8) ret2 += B[i][0];
	cout << (ret2 % mod) << endl;
}
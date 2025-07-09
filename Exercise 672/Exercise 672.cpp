#include<bits/stdc++.h>
using namespace std;

template <int MOD_> struct modnum {
	static constexpr int MOD = MOD_;
	static_assert(MOD_ > 0, "MOD must be positive");

private:
	using ll = long long;

	int v;

	static int minv(int a, int m) {
		a %= m;
		assert(a);
		return a == 1 ? 1 : int(m - ll(minv(m, a)) * ll(m) / a);
	}

public:

	modnum() : v(0) {}
	modnum(ll v_) : v(int(v_ % MOD)) { if (v < 0) v += MOD; }
	explicit operator int() const { return v; }
	friend std::ostream& operator << (std::ostream& out, const modnum& n) { return out << int(n); }
	friend std::istream& operator >> (std::istream& in, modnum& n) { ll v_; in >> v_; n = modnum(v_); return in; }

	friend bool operator == (const modnum& a, const modnum& b) { return a.v == b.v; }
	friend bool operator != (const modnum& a, const modnum& b) { return a.v != b.v; }

	modnum inv() const {
		modnum res;
		res.v = minv(v, MOD);
		return res;
	}
	modnum neg() const {
		modnum res;
		res.v = v ? MOD-v : 0;
		return res;
	}
	modnum operator- () const {
		return neg();
	}
	modnum operator+ () const {
		return modnum(*this);
	}

	modnum& operator ++ () {
		v ++;
		if (v == MOD) v = 0;
		return *this;
	}
	modnum& operator -- () {
		if (v == 0) v = MOD;
		v --;
		return *this;
	}
	modnum& operator += (const modnum& o) {
		unsigned int v_ = unsigned(v) + unsigned(o.v);
		if (v_ >= MOD) v_ -= MOD;
		v = int(v_);
		return *this;
	}
	modnum& operator -= (const modnum& o) {
		v -= o.v;
		if (v < 0) v += MOD;
		return *this;
	}
	modnum& operator *= (const modnum& o) {
		v = int(ll(v) * ll(o.v) % MOD);
		return *this;
	}
	modnum& operator /= (const modnum& o) {
		return *this *= o.inv();
	}

	friend modnum operator ++ (modnum& a, int) { modnum r = a; ++a; return r; }
	friend modnum operator -- (modnum& a, int) { modnum r = a; --a; return r; }
	friend modnum operator + (const modnum& a, const modnum& b) { return modnum(a) += b; }
	friend modnum operator - (const modnum& a, const modnum& b) { return modnum(a) -= b; }
	friend modnum operator * (const modnum& a, const modnum& b) { return modnum(a) *= b; }
	friend modnum operator / (const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
using num = modnum<1117117717>;

using ll = long long;

template <typename T> T pow(T a, ll b) { T r = 1; while (b) { if (b & 1) r *= a; a *= a; b >>= 1; } return r; }

num S(vector<int> digs) {
	while (!digs.empty() && digs.back() == 0) digs.pop_back();
	num res = 0;
	int pref = 0;
	for (int i = int(digs.size()) - 1; i >= 0; pref += 6 - digs[i], i--) {
		int d = digs[i];
		num avg_value = (num(pref) + num(12 - d + 1) / num(2) + num(i) * num(3));
		res += avg_value * num(d) * pow(num(7), i);
	}
	assert(digs.empty() || digs.back() > 0);
	for (int i = 0; i < int(digs.size()); i++) {
		res -= 6 * pow(num(7), i);
	}
	return res;
}

num Hslow(ll K) {
	assert(K % 10 == 0);
	K /= 10;
	// repeating sequence of digits: 0431162355
	string digits = "0431162355";

	string N;
	for (int i = 0; i < K; i++) {
		N += digits;
	}
	reverse(N.begin(), N.end());

	vector<int> digs;
	for (char c : N) digs.push_back(c - '0');
	return S(digs);
}

template <typename num>
vector<num> BerlekampMassey(const vector<num>& s) {
	int n = int(s.size()), L = 0, m = 0;
	vector<num> C(n), B(n), T;
	C[0] = B[0] = 1;

	num b = 1;
	for(int i = 0; i < n; i++) { ++m;
		num d = s[i];
		for (int j = 1; j <= L; j++) d += C[j] * s[i - j];
		if (d == 0) continue;
		T = C; num coef = d / b;
		for (int j = m; j < n; j++) C[j] -= coef * B[j - m];
		if (2 * L > i) continue;
		L = i + 1 - L; B = T; b = d; m = 0;
	}

	C.resize(L + 1); C.erase(C.begin());
	for (auto& x : C) {
		x = -x;
	}
	return C;
}

template <typename num>
num linearRec(const vector<num>& S, const vector<num>& tr, long long k) {
	int n = int(tr.size());
	assert(S.size() >= tr.size());

	auto combine = [&](vector<num> a, vector<num> b) {
		vector<num> res(n * 2 + 1);
		for (int i = 0; i <= n; i++) for (int j = 0; j <= n; j++) res[i + j] += a[i] * b[j];
		for (int i = 2 * n; i > n; --i) for (int j = 0; j < n; j++)
			res[i - 1 - j] += res[i] * tr[j];
		res.resize(n + 1);
		return res;
	};

	vector<num> pol(n + 1), e(pol);
	pol[0] = e[1] = 1;

	for (++k; k; k /= 2) {
		if (k % 2) pol = combine(pol, e);
		e = combine(e, e);
	}

	num res = 0;
	for (int i = 0; i < n; i++) res += pol[i + 1] * S[i];
	return res;
}

num H(ll K) {
	assert(K % 10 == 0);
	vector<num> S;
	for (int i = 0; i < 300; i += 10) {
		S.push_back(Hslow(i));
	}
	auto tr = BerlekampMassey(S);
	//cerr << tr.size() << '\n';
	return linearRec(S, tr, K / 10);
}

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0);
	cerr << Hslow(10) << '\n';
	cout << H(1e9) << '\n';

	return 0;
}
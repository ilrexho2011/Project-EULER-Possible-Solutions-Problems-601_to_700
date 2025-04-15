#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod = 1e9 + 7;

namespace Binomial
{
    const ll mod = 1e9 + 7;
    vector<ll> fac, finv;

    void init(int n) {
        fac.resize(n);
        finv.resize(n);
        fac[0] = 1;
        for (int i = 1; i < n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
        finv[1] = 1;
        for (int i = 2; i < n; i++) {
            finv[i] = finv[mod % i] * (mod - mod / i) % mod;
        }
        finv[0] = 1;
        for (int i = 1; i < n; i++) {
            finv[i] = finv[i - 1] * finv[i] % mod;
        }
    }
    ll C(ll n, ll m) {
        return fac[n] * finv[m] % mod * finv[n - m] % mod;
    }
}

int main(int argc, char const *argv[]) {
	Binomial::init(1e5);
        ll k0 = 308 * (Binomial::C(9999,0));

	ll k1 = 1601 * (Binomial::C(9999,1));

	ll k2 = 5169 * (Binomial::C(9999,2));

	ll k3 = 11238 * (Binomial::C(9999,3));

	ll k4 = 17136 * (Binomial::C(9999,4));

	ll k5 = 18642 * (Binomial::C(9999,5));

	ll k6 = 14451 * (Binomial::C(9999,6));

	ll k7 = 7819 * (Binomial::C(9999,7));

	ll k8 = 2812 * (Binomial::C(9999,8));

	ll k9 = 605 * (Binomial::C(9999,9));

	ll k10 = 59 * (Binomial::C(9999,10));

	ll ans = k0 + k1 + k2 + k3 + k4 +k5 + k6 + k7 + k8 + k9 + k10;

	std::cout << ans % mod << '\n';
	cerr << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
	return 0;
}
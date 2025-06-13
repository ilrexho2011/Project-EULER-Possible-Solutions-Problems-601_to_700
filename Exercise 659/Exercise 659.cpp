#include <iostream>
#include "lib/primes.cpp"
#include "lib/field.cpp"
#include "lib/tonelli-shanks.cpp"

using namespace std;
constexpr long long M = 1e18, K = 1e7;
using F = Field<M>;

int main(){
	sieve(2*K+10);

	vector<long long> lpf(K+1, 0), remainder(K+1);
	for(long long k = 0; k <= K; ++k) remainder[k] = 4*k*k+1;
	for(auto p : primes){
		if(p==2) continue;
		// 4*k*k+1 = 0 -> k = sqrt(-1)/2
		auto i = sqrtp(-1, p);
		if(i == -1) continue; // Edge case if -1 is not a square mod p.

		for(auto r : {i*(p+1)/2, -i*(p+1)/2})
			for(r = mod(r, p); r <= K; r += p){
				lpf[r] = p;
				while(remainder[r] % p == 0) remainder[r]/=p;
			}
	}

	F ans = 0; // Mod 1e18
	for(long long k = 1; k<=K; ++k) ans += max(lpf[k], remainder[k]);
	cout << ans << endl;
}
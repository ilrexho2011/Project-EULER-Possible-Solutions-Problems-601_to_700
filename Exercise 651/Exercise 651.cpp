#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

const LL MOD = 1000000007;
LL powmod(LL a, LL n){
	if(n == 0) return 1;
	if(n % 2) return (a*powmod(a,n-1)) % MOD;
	LL c = powmod(a, n/2);
	return (c*c) % MOD;
}
LL inv(LL a){
	return powmod(a, MOD-2);
}
LL fact[110000];
LL invfact[110000];

LL ncr(LL n, LL r){
	if(r < 0 || n < 0) return 0;
	if(n < r) return 0;
	LL a = fact[n];
	a = (a * invfact[r]) % MOD;
	a = (a * invfact[n-r]) % MOD;
	return a;
}
void init(){
	fact[0] = 1;
	invfact[0] = 1;
	LL inv2 = inv(2);
	for(LL i = 1; i < 110000; i++){
		fact[i] = (i*fact[i-1]) % MOD;
		invfact[i] = inv(fact[i]);
	}
}

LL cnt_fast(LL m, LL expo){
	LL ans = 0;
	for(int v = 0; v <= m; v++){
		ans = ans + powmod(m-v, expo) * (powmod(-1, v) * ncr(m, v) % MOD);
		ans %= MOD;
	}
	if(ans < 0) ans += MOD;
	return ans;
}


LL f_fast(LL m, LL a, LL b){
	LL tot = (4 * a * b) % MOD;
	LL ans = 0;
	map<LL,LL> freqa, freqb;
	vector<LL> ca(3, 0), cb(3, 0);
	for(LL i = 0; i < a; i++) freqa[a / __gcd(a, i)]++;
	for(LL i = 0; i < b; i++) freqb[b / __gcd(b, i)]++;
	for(LL i = 0; i < a; i++){
		if(a % 2){
			ca[1]++;
		} else if(i % 2){
			ca[2]++;
		} else {
			ca[0]++;
		}
	}
	for(LL i = 0; i < b; i++){
		if(b % 2){
			cb[1]++;
		} else if(i % 2){
			cb[2]++;
		} else {
			cb[0]++;
		}
	}
	for(auto x : freqa){
		for(auto y : freqb){
			LL cnt = x.second * y.second % MOD;
			if(!cnt) continue;
			LL ord = x.first * y.first / __gcd(x.first, y.first);
			ans += cnt * cnt_fast(m, a * b / ord);
			ans %= MOD;
		}
	}
	for(int i = 0; i < 3; i++){
		for(int j = 0; j < 3; j++){
			LL cnt = ca[i] * cb[j] % MOD;
			if(!cnt) continue;
			ans += cnt * cnt_fast(m, (a * b + i * j)/ 2);
			ans %= MOD;
		}
	}
	for(auto x : freqa){
		for(int j = 0; j < 3; j++){
			LL cnt = x.second * cb[j] % MOD;
			if(!cnt) continue;
			LL f = 0;
			if(x.first % 2 == 0){
				f += a * (b - j) / x.first;
			} else {
				f += a * (b - j) / x.first / 2;
			}
			f += j * a / x.first;
			ans += cnt * cnt_fast(m, f);
			ans %= MOD;
		}
	}
	for(int i = 0; i < 3; i++){
		for(auto y : freqb){
			LL cnt = ca[i] * y.second % MOD;
			if(!cnt) continue;
			LL f = 0;
			if(y.first % 2 == 0){
				f += (a - i) * b / y.first;
			} else {
				f += (a - i) * b / 2 / y.first;
			}
			f += i * b / y.first;
			ans += cnt * cnt_fast(m, f);
			ans %= MOD;
		}
	}
	// x,y -> x+r,y+s
	// x,y -> x+r,s-y
	// x,y -> r-x,s+y
	// x,y -> r-x,s-y
	if(ans < 0) ans += MOD;
	return ans * inv(tot) % MOD;
}
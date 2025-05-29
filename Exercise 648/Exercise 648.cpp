#include <iostream>
#include <vector>
using namespace std;
constexpr int N = 1000, M = 1e9, K = 2*N+2;
using P = vector<long long>; // Supports basic + , unary -, and * operations

P operator-(const P&p){
	P a = p;
	for(auto &x : a) x = -x;
	return a;
}
P operator+(const P&l, const P&r){
	P a;
	if(l.size() < r.size()){
		a = r;
		for(int i = 0; i < l.size(); ++i) a[i] += l[i];
	} else {
		a = l;
		for(int i = 0; i < r.size(); ++i) a[i] += r[i];
	}
	if(a.size() > N + 1) a.resize(N+1);
	for(auto &x : a) x %= M;
	return a;
}
P operator*(const P&l, const P&r){
	P a(l.size() + r.size() - 1);
	for(int i = 0; i < l.size(); ++i)
		for(int j = 0; j < r.size(); ++j)
			a[i+j] += l[i] * r[j] % M;
	if(a.size() > N + 1) a.resize(N+1);
	for(auto &x : a) x %= M;
	return a;
}

int main(){
	vector<P> a(K+1);
	a[0] = {1};
	for(int i = 1; i < a.size(); ++i) a[i] = P{1} + P{-1, 1} * a[i-1];
	P ans{1};
	a[0] = {0, 1}; // Edge case because the 1st jump is not length 0.
	for(int step = K; step >= 0; step -= 2) ans = (P{1} + -a[step]) * (P{1} + ans);
	long long sum = 0;
	for(int i = 0; i <= N; ++i) sum += ans[i];
	cout << sum%M << endl;
}
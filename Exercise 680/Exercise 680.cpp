#include<bits/stdc++.h>
#define ALL(c) begin(c), end(c)
using namespace std;
using ll = long long;
using ld = long double;


#define _len(v) ((v) ? (v)->len : 0)

struct node{
	node *l, *r;
	ll len;
	ll L, R;
	bool rev, isleaf;
	
	node(ll L, ll R) : L(L), R(R){
		rev = false;
		len = abs(L-R) + 1;
		l = r = nullptr;
		isleaf = true;
	}
	
	node(node *l, node *r) : l(l), r(r) {
		len = _len(l) + _len(r);
		rev = false;
		isleaf = false;
	}
};

void push(node *v){
	if(!v || !v->rev) return ;
	if(v->isleaf){
		swap(v->L, v->R);
	}else{
		if(v->l) v->l->rev^=1;
		if(v->r) v->r->rev^=1;
		swap(v->l, v->r);
	}
	v->rev = false;
}

void upd(node *v){
	if(!v) return ;
	if(v->isleaf) return ;
	v->len = _len(v->l) + _len(v->r);
}

void cut(node *v, ll x, node *&l, node *&r){
	assert(v!=nullptr);
	push(v);
	
	assert(0<=x);
	if(x>=_len(v)){
		l = v;
		r = nullptr;
		return ;
	}
	
	
	if(v->isleaf){
		ll L = v->L, R = v->R;
		ll dx = L < R ? +1 : -1;
		ll M = L + x*dx;
		l = x==0 ? nullptr : new node(L, M-dx);
		r = x==0 ? v : new node(M, R);
		return ;
	}
	
	if(x < _len(v->l)){
		cut(v->l, x, l, v->l);
		r = v;
	}else{
		cut(v->r, x-_len(v->l), v->r, r);
		l = v;
	}
	
	upd(l);
	upd(r);
}



void print(node *v, char c = '\n'){
	cout<<"(";
	if(v){
		push(v);
		if(v->isleaf) cout<<v->L<<'-'<<v->R;
		else{
			print(v->l, ' ');
			print(v->r, ' ');
		}
	}
	cout<<")="<<_len(v)<<c;
}


////-------------------------------------------------


void fibo(vector<ll> &f, ll mod, int n){
	f = {0,1,1};
	while(size(f)<=n){
		int i = size(f);
		f.push_back((f[i-1]+f[i-2]) %mod);
	}
}


const int mod = 1e9;
const ll sum_for_1_to_mod = (1LL+mod)*mod/2 %mod;

ll sumk(ll i, ll j){
	return __int128(i+j)*(j-i+1)/2 %mod;
}

ll sumk2(ll i, ll j){
	if(i>0) return (sumk2(0,j) - sumk2(0,i-1) + mod) %mod;
	if(j==0) return 0;
	if(j>=mod) return (sumk2(0,j%mod) + (j/mod)%mod*sum_for_1_to_mod) %mod;
	
	if(j%2==1) return (sumk2(0,j-1) + j*j) %mod;
	
	ll res = (sumk2(0,j/2)*4*2 - sumk(0, j/2)*4%mod+mod + j/2) %mod;
	
	return res;
}

ll cnt = 0;
ll F(ll L, ll R, ll i, ll j){
	ll dx = L<=R ? 1 : -1;
	ll sum = (L%mod - dx*i%mod + mod)%mod * sumk(i,j) %mod;
	sum = (sum + (sumk2(i,j)*dx%mod+mod)) %mod;
	return sum;
}


void calc(node *v, ll &ans, ll pref){
	if(!v) return ;
	push(v);
	if(v->isleaf){
		ans+=F(v->L, v->R, pref, pref+_len(v)-1);
		ans%=mod;
	}else{
		calc(v->l, ans, pref);
		calc(v->r, ans, pref+_len(v->l));
	}
}

ll solve_fast(ll n, int m){
	vector<ll> f;
	fibo(f, n, m*2);
	
	node *v = new node(0, n-1);
	
	for(int i=1;i<=m;++i){
		//if(i%100==0) cerr<<i<<"...\n";
		
		ll L = f[i*2-1], R = f[i*2];
		if(L>R) swap(L,R);
		
		node *a, *b;
		cut(v, R+1, a, b);
		cut(a, L, a, v);
		v->rev^=1;
		
		if(i&1) a = new node(a, v);
		else b = new node(v, b);
		v = new node(a,b);
	}
	
	ll ans = 0;
	calc(v, ans, 0);
	
	return ans;
}

int main(){
	//freopen("input.txt","r",stdin); //freopen("output.txt","w",stdout);
	ios::sync_with_stdio(0);cin.tie(0);//cout.precision(12);cout<<fixed;
	
	
	cout<<solve_fast(5,4)<<endl;
	cout<<solve_fast(100,100)<<endl;
	cout<<solve_fast(1e4,1e4)<<endl;
	cout<<solve_fast(1e18,1e6)<<endl;
	
	
	return 0;
}

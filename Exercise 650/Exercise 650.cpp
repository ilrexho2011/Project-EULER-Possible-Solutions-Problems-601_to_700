#include "bits/stdc++.h"
using namespace std;
/////////////////// TYPES & MACROS ///////////////////////////////
#define mp make_pair
#define eb emplace_back
#define pb push_back
#define all(x) x.begin(),x.end()
#define ff first
#define ss second
#define vv vector
#define exist(s,e) (s.find(e)!=s.end())
#define sz(x) ((int)(x).size())
#define int ll
#define el '\n'
typedef long long ll; typedef long double ld; typedef double dd;typedef vector<int> vi; typedef pair<int, int> pii;typedef pair<ll,ll> pll;
const ll INFLL=0x7f7f7f7f7f7f7f7f, MOD=1e9+7; const int INF=0x7f7f7f7f;
///if(///////////////// DEBUG /////////////////////////////////////////
#define D(x) cerr<<#x<<" is:\t"<<x<<'\n';
#define DD(x,y) cerr<<'('<<#x<<','<<#y<<") are:\t"<<x<<' '<<y<<'\n';
#define DDD(x,y,z) cerr<<'('<<#x<<','<<#y<<','<<#z<<") are:\t"<<x<<' '<<y<<' '<<z<<'\n';
/////////////////// VARIABLES & FUNCTIONS//////////////////////////
vv<vv<int>> adj; vi vis, color; 
int dx8[]={0,1,1,1,0,-1,-1,-1}, dy8[]={1,1,0,-1,-1,-1,0,1},dx4[]={0,1,0,-1}, dy4[]={1,0,-1,0};
inline ll mexp(ll x,ll n,ll m=MOD){ll res=1;x%=m;while(n){if(n&1)res=(res*x)%m;n>>=1;x=(x*x)%m;}return res;}
inline ll gcd(ll a, ll b){while (a>0 && b>0){if(a>b)a%=b;else b%=a;}return a+b;}


template <int MOD=1'000'000'007>
struct Modular {
  int value;
  static const int MOD_value = MOD;

  Modular(long long v = 0) { value = v % MOD; if (value < 0) value += MOD;}
  Modular(long long a, long long b) : value(0){ *this += a; *this /= b;}

  Modular& operator+=(Modular const& b) {value += b.value; if (value >= MOD) value -= MOD; return *this;}
  Modular& operator-=(Modular const& b) {value -= b.value; if (value < 0) value += MOD;return *this;}
  Modular& operator*=(Modular const& b) {value = (long long)value * b.value % MOD;return *this;}

  friend Modular mexp(Modular a, long long e) {
    Modular res = 1; while (e) { if (e&1) res *= a; a *= a; e >>= 1; }
    return res;
  }
  friend Modular inverse(Modular a) { return mexp(a, MOD - 2); }

  Modular& operator/=(Modular const& b) { return *this *= inverse(b); }
  friend Modular operator+(Modular a, Modular const b) { return a += b; }
  friend Modular operator-(Modular a, Modular const b) { return a -= b; }
  friend Modular operator-(Modular const a) { return 0 - a; }
  friend Modular operator*(Modular a, Modular const b) { return a *= b; }
  friend Modular operator/(Modular a, Modular const b) { return a /= b; }
  friend std::ostream& operator<<(std::ostream& os, Modular const& a) {return os << a.value;}
  friend bool operator==(Modular const& a, Modular const& b) {return a.value == b.value;}
  friend bool operator!=(Modular const& a, Modular const& b) {return a.value != b.value;}
};


///////////////////// MAIN STARTS //////////////////////////////////
int32_t main(void){
ios_base::sync_with_stdio(false);cin.tie(NULL); cout.tie(NULL);
cout<<fixed;cerr<<fixed; cout<<setprecision(10); cerr<<setprecision(3);
mt19937 genr(chrono::high_resolution_clock::now().time_since_epoch().count());


int p; cin>>p;
vi prime(p), fac(p,0), psum(p,0);
for(int i=0;i<p;++i) cin>>prime[i];
typedef Modular<1'000'000'007> modulo;
modulo ans=0;
for(int n=2;n<=20'000;++n){
	modulo t=1,inv=1;
	for(int i=0, temp=n;i<p && temp>1;++i){
		while(temp%prime[i]==0) fac[i]++,temp/=prime[i];
	}
	for(int i=0;prime[i]<=n && i<p;++i){
		psum[i]+=fac[i];
		t*=mexp(prime[i],(n+1)*fac[i]-2*psum[i]+1,MOD)-1;
		inv*=prime[i]-1;
	}
	ans+=t;
}
cout<<ans+1<<el;

return 0;
}

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

//1000000000000

typedef  int long long ll ;
#define n 1000000000000
#define a 10000000
#define mod 1000000007

ll powerMod(ll x, ll y, ll m) 
{ 
    ll res = 1; 
    x = x % m; 
    while (y > 0) 
    { 
        if (y & 1) 
            res = (res*x) % m; 
        y = y>>1;
        x = (x*x) % m;   
    } 
    return res; 
} 

void printList(vector<ll> v,string s) {
    cout << s;
    for (int i = 0; i < v.size(); ++i) {
            cout << v[i] << ", ";
    }
    cout << endl;
}

int main() {
 
    vector<ll> pows(a+1, 0);
    vector<ll> invs(a+1, 0);
    vector<ll> choose;
    vector<ll> coeff;
    vector<ll> bCoeff(a+1, 0);

    cout << "step 1 ...  " << endl;
    invs[0]=0;
    invs[1]=1;
    for (ll j = 2;j<=a; j++) {
        invs[j] = powerMod(j, mod-2, mod);
    }
    cout << "step 1 ... inverses calculated " << endl;
    //printList(invs,"invs = ");

    cout << "step 2 ...  " << endl;
    for (ll j = 2;j<a+1; j++) {
        pows[j] = powerMod(j, n+1, mod);
        pows[j] = ((pows[j]-1) * invs[j-1]) % mod;
    }
    cout << "step 2 ... powers and facts calculated " << endl;
    //printList(facts,"facts = ");
    // 


    cout << "step 3 ...  " << endl;
 
    bCoeff[0] = ((a % 2 == 1) ? 0 : 1);
    ll binomial = 1;

    for (ll j = 1;j<a+1; j++) {
        binomial = (binomial * (a+1-(j-1))) % mod;
        binomial = (binomial * invs[j]) % mod;
        bCoeff[j] = (invs[2] * (binomial - bCoeff[j-1])) % mod;
    }

    cout << "step 3 ... coefficients calculated " << endl;
    
    ll nMod = (n + 1) % mod;
    ll sumRes = 0;
    ll res = 0;
    coeff.push_back(0);
    coeff.push_back(1);

    res =  (nMod*(bCoeff[1]+1)) % mod; 

    for (ll k=2;k<=a;k++) {        
        res = (res + ((-1 + 2*((k) % 2)) * (bCoeff[k] + (-1 + 2*((k) % 2))))* pows[k]) % mod;
        //cout << k << " - res = " << res << endl;
    }

    cout << "result = " << (mod + res) % mod << endl;
    return 0;

}

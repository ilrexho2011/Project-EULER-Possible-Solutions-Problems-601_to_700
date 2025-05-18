#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

typedef  int long long ll ;
#define mLim 201820182018
#define n 449244+1 // floor(sqrt(nLim)) +1
#define mod 1000000000

ll arr [n] = {0};
vector<ll> primes;
vector<ll> primes2;
ll harr [n] = {0};
vector<ll> p2index;


int main() {
    ll counter = 0;
    ll whilecounter = 0;
    ll sumcounter = 0;
    harr[1] = -1;
    ll res = 0;
    ll res1 = 0;
    ll lenPrimes = 0;
    arr[0]=0;

/*
*/

    //Initialise array of primes up to Sqrt(mLim) to sieve/reduce later
    for (ll k = 1; k < n; k++){
        arr[k] = k; //initialise arr as well
        if (harr[k] == 0){
            primes.push_back(k);
            p2index.push_back(k);
            lenPrimes++;
            for(int i = 2*k; i < n; i += k){
                harr[i] = -1;
                //counter++;
            }
        }

    }
    cout << "Initialised Primes to Use: there are " << lenPrimes << "  primes - last prime = " << primes[lenPrimes-1] << " - last index = " << p2index[lenPrimes-1] << endl;

    for(ll m = 1; m <=mLim/(n-1); m += 1){
        cout << "Initialised ARR at m = "<< m << endl;
        ll mn = m*(n-1);
        for (ll k=0; k < lenPrimes; k++){
            
            ll p = primes[k];
            for (ll j = p2index[k]; j<n; j += p){

                while( arr[j] % p ==0) {
                    arr[j] /= p;
                }
				if (arr[j] == 1){
					arr[j] = p;
				}
            }
            
            p2index[k] = ((mn/p + 1) * p - mn);
        
        }

        for (ll k = 1; k<n; k++){
			//counter++;
            res = (res + arr[k]) % mod;
            arr[k] = mn + k;
        }
    }
    
    cout << "result = " << res <<  endl;
    
    return 0;

}
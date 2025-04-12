
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <math.h>
#include <map>

std::vector<uint32_t> phisum;
std::map<uint64_t, uint64_t> memopad;
const uint32_t mod = 998244353, nr=400000;

void totientsum() {
    phisum.resize(nr+1); std::iota(phisum.begin(),phisum.end(),0);
    for(uint64_t i = 2; i<=nr; i++) {
        if(phisum[i]==i)
            for(uint64_t t=i;t<=nr;t+=i)
                phisum[t] = (uint32_t)((phisum[t]*(i-1))/i);
        phisum[i] = (phisum[i]+phisum[i-1])%mod;
    }
}

uint64_t totientsum_iterator(uint64_t n) { /* call totientsum() before this */
    if(n<=nr) return phisum[n]%mod;
    if(memopad[n]) return memopad[n];
    uint64_t sum = ((n&0x1)?(n%mod)*(((n+1)>>1)%mod):((n>>1)%mod)*((n+1)%mod))%mod;
    uint64_t m=2;
    while(true){
        uint64_t x = n/m;
        uint64_t nxt = n/x;
        if(nxt >= n) return memopad[n] = (sum + mod - (((n-m+1)%mod)*(totientsum_iterator(n/m)%mod)%mod))%mod;
        sum = (sum + mod-(((nxt-m+1)%mod)*(totientsum_iterator(n/m)%mod)%mod))%mod;
        m = nxt+1;
    }
}

uint64_t calcdd(uint64_t n) {
    return ((n&0x1)?(n%mod)*(((n+1)>>1)%mod):((n>>1)%mod)*((n+1)%mod))%mod;
}

void problem625() {
    uint64_t n = 100000000000, sum=0, q = int(sqrt(n)), r = int(n/q);
    totientsum();
    for(uint64_t i=1;i<=r;i++)
        sum = (sum+(i*totientsum_iterator(n/i)))%mod;
    
    for(uint64_t i=1;i<q;i++) {
        uint64_t val = (calcdd(n/i)+mod-calcdd(n/(i+1)))%mod;
        sum = (sum+(val*totientsum_iterator(i)))%mod;
    }
    std::cout << sum << std::endl;
}
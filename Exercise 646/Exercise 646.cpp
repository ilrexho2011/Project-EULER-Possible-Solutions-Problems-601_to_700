#include <cstdio>
#include <cmath>
#include <map>
#include <vector>
#include <algorithm>
#include <cassert>
const int N=70;
const long double L=20*logl(10)-(1e-20),H=60*logl(10)+(1e-20);
const long long MOD=1000000007LL;
bool sieve[N+1];
int primes[N+1],top=0;
int bin[N];
void init()
{
    for (int i=2;i<=N;++i)
        if (!sieve[i])
        {
            primes[top++]=i;
            for (int j=i;j<=N/i;++j)
                sieve[i*j]=true;
        }
    long long num_divisors=1;
    for (int i=0;i<top;++i)
    {
        for (int j=primes[i];j<=N;j*=primes[i])
            bin[i]+=N/j;
        printf("%d ",bin[i]);
        num_divisors*=(bin[i]+1);
    }
    printf("\n%lld\n",num_divisors),fflush(stdout);
}
std::map<long double,long long> table;
void _gen(int now,long long prod,long double val,const long double &up,const int &bound)
{
    //printf("%d %lf\n",now,val);
    if (now==bound+1)
    {
        if (table.find(val)==table.end()) table[val]=prod;
        else table[val]=(table[val]+prod)%MOD;
        return ;
    }
    for (long long i=0,j=1;i<=bin[now];++i,j=j*(-primes[now])%MOD)
        if (val+i*logl(primes[now])<=up)
        {
            _gen(now+1,prod*j%MOD,val+i*logl(primes[now]),up,bound);
        }
}
long long _gen2(int now,long long prod,long double val,const long double &up,const int &bound,
                const std::vector<long double> &keys,const std::vector<std::pair<long double,long long>> &li)
{
    if (now==bound)
    {
        //long long sum=0;
        //for (std::pair<long double,long long> i:table)
        //    if (i.first<=up-val) sum=(sum+i.second)%MOD;
        int idx=std::upper_bound(keys.begin(),keys.end(),up-val)-keys.begin();
        --idx;
        long long sum2=li[idx].second%MOD;
        //assert(sum==sum2);
        return prod*sum2%MOD;
    }
    long long ret=0;
    for (long long i=0,j=1;i<=bin[now];++i,j=j*(-primes[now])%MOD)
        if (val+i*logl(primes[now])<=up)
        {
            ret=(ret+_gen2(now-1,prod*j%MOD,val+i*logl(primes[now]),up,bound,keys,li))%MOD;
        }
    return ret%MOD;
}
long long gen(long double up)
{
    table.clear();
    const int bound=std::min(top/2,5);
    printf("gen begin,bound=%d\n",bound),fflush(stdout);
    _gen(0,1,0,up,bound);
    printf("gen finished\n"),fflush(stdout);
    std::vector<std::pair<long double,long long>> li(table.begin(),table.end());
    std::vector<long double> keys;
    for (size_t i=0;i<li.size();++i)
        keys.emplace_back(li[i].first);
    for (size_t i=1;i<li.size();++i)
        li[i].second=(li[i].second+li[i-1].second)%MOD;
    printf("first finished\n"),fflush(stdout);
    return _gen2(top-1,1,0,up,bound,keys,li);
}
int main()
{
    init();
    printf("%lld\n",(gen(H)-gen(L)+MOD)%MOD);
    return 0;
}
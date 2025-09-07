#include <cstdio>
#include <cmath>
#include <unordered_set>
#include <set>
#include <vector>
#include <unordered_map>
#include <cassert>
#include <algorithm>
const long long N=1e14;
//const long long N=100000000000000LL;
const long long UP=sqrt(N+0.5)*2;
const int Q=700;
bool sieve[UP+100];
int primes[UP],top=0;
std::set<int> li;
std::unordered_map<int,int> jump;
void init()
{
    for (long long i=2;i<=UP;++i)
        if (!sieve[i])
        {
            primes[top++]=i;
            for (long long j=i;j<=UP/i;++j)
                sieve[i*j]=true;
        }
    for (int _b=0;_b<std::min(top,Q);++_b)
    {
        long long b=primes[_b];
        for (__int128 i=b,j=1+b;i<=N;i*=b,j+=i)
        {
            assert(j>0);
            __int128 m=j;
            long long idx=top;
            if (!(primes[top-1]<=m/primes[top-1]))
                idx=std::upper_bound(primes,primes+top,(int)sqrt(m+0.5))-primes;
            std::unordered_set<int> bucket;
            #pragma omp parallel for
            for (int t=0;t<idx;++t)
                if (m%primes[t]==0)
                {
                    #pragma omp critical
                    {
                        li.emplace(primes[t]);
                        if (b>primes[t])
                        {
                            if (jump.find(primes[t])==jump.end()) jump.emplace(primes[t],b);
                            else if (jump.at(primes[t])>b) jump.at(primes[t])=b;
                        }
                        bucket.emplace(primes[t]);
                    }
                }
            m=j;
            for (const auto &t:bucket)
                for (;m%t==0;m/=t);
            if (m>1 && m<=UP)
            {
                li.emplace(m);
                if (b>m)
                {
                    if (jump.find(m)==jump.end()) jump.emplace(m,b);
                    else if (jump.at(m)>b) jump.at(m)=b;
                }
            }
        }
        if (_b%1000==0) printf("init %d finished, total = %d\n",_b,top),fflush(stdout);
    }
}
long long gcd(long long x,long long y)
{
    return y?gcd(y,x%y):x;
}
__int128 gcd(__int128 x,__int128 y)
{
    return y?gcd(y,x%y):x;
}
long long ans=0;
std::unordered_set<long long> candidates;
inline void update(long long x)
{
    if (candidates.find(x)==candidates.end())
    {
        candidates.emplace(x);
        ans+=x;
        printf("%lld %lld\n",x,ans),fflush(stdout);
    }
}
inline std::pair<__int128,long long> mult(const std::pair<__int128,long long> &o1,const std::pair<__int128,long long> &o2)
{
    long long g1=gcd(o1.first,(__int128)o2.second),g2=gcd((__int128)o1.second,o2.first);
    return std::make_pair(o1.first/g1*(o2.first/g2),o1.second/g2*(o2.second/g1));
}
int main()
{
    init();
    std::unordered_set<long long> bbb;
    for (long long i=3;i<=N;i*=3)
        bbb.emplace(i);
    std::vector<std::pair<std::pair<__int128,long long>,long long>> li2;
    li2.emplace_back(std::make_pair(1,1),1);
    long long cnt=0;
    for (const auto &i:li)
    {
        std::vector<std::pair<__int128,long long>> li3;
        for (__int128 j=i,k=1+i;j<=N && j>0;j*=i,k+=j)
            li3.emplace_back(k,j);
        std::vector<std::pair<std::pair<__int128,long long>,long long>> next;
        #pragma omp parallel for
        for (long long _j=0;_j<(long long)li2.size();++_j)
        {
            const auto &j=li2.at(_j);
            for (long long _k=0;_k<(long long)li3.size();++_k)
            {
                const auto &k=li3.at(_k);
                if (j.second<=N/k.second)
                {
                    std::pair<__int128,long long> temp=mult(j.first,k);
                    if (!(i>3 && temp.second%3))
                    {
                        long long val=j.second*k.second;
                        auto func=[&](const std::pair<__int128,long long> &temp,const long long &val)->void{
                            next.emplace_back(temp,val);
                            if (bbb.find(temp.second)!=bbb.end()) update(val);
                        };
                        if (i>3)
                        {
                            if (temp.second%i==0)
                            {
                                if (jump.find(i)!=jump.end() && jump.at(i)<=N/val)
                                {
                                    #pragma omp critical
                                    func(temp,val);
                                }
                            }
                            else
                            {
                                #pragma omp critical
                                func(temp,val);
                            }
                        }
                        else
                        {
                            #pragma omp critical
                            func(temp,val);
                        }
                    }
                }
                else break;
            }
        }
        li2.insert(li2.end(),next.begin(),next.end());
        printf("%lld finished, total = %lld, size = %lld, ans = %lld\n",cnt,(long long)li.size(),(long long)li2.size(),ans),fflush(stdout);
        ++cnt;
    }
    printf("%lld\n",ans);
    return 0;
}
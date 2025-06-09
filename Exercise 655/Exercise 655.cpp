#include <cstdio>
#include <map>
#include <sstream>
#include <iostream>
//const long long N=5;
//const long long MOD=109;
const long long N=32;
const long long MOD=10000019LL;
long long pow(long long x,long long y)
{
    long long ret=1;
    for (;y;y>>=1,x=x*x)
        if (y&1) ret*=x;
    return ret;
}
long long powmod(long long x,long long y)
{
    long long ret=1;
    for (x%=MOD;y;y>>=1,x=x*x%MOD)
        if (y&1) ret=ret*x%MOD;
    return ret;
}
std::string toString(const long long &x)
{
    std::stringstream ss;
    ss<<x;
    return ss.str();
}
long long calc(const std::string &str,const long long &tot)
{
    long long ret=0;
    for (int i=str.size()-1,j=tot;j>0;--i,--j)
        ret=(ret*10%MOD+(i>=0?(str[i]-'0'):0))%MOD;
    return ret;
}
long long calc(const long long &x,const long long &tot)
{
    if (tot==0) return 0;
    long long base=1,len=1;
    for (long long n=x;n>=10;++len,base*=10,n/=10);
    long long ret=0;
    for (long long n=x;n;base/=10,n/=10)
        ret=(ret+n%10*(base%MOD)%MOD)%MOD;
    for (long long i=len;i<tot;++i)
        ret=ret*10%MOD;
    return ret;
}
int main()
{
    long long ans=0;
    for (long long len=3;len<=N;++len)
    {
        long long chunk=len/4;
        if (len%4) ++chunk;
        long long mid=len-chunk*2;
        long long left=mid/2;
        // chunk (left ? left) chunk
        long long b1=pow(10,chunk),b2=pow(10,left),b3=powmod(10,len-chunk);
        std::map<int,long long> li;
        if (mid%2==0)
        {
            for (long long i=0;i<b2;++i)
            {
                long long rem=(i%MOD*(b2%MOD)%MOD+calc(i,left))%MOD;
                rem=(rem+MOD)%MOD;
                int key=(rem*(b1%MOD)%MOD);
                ++li[key];
            }
        }
        else
        {
            for (long long i=0;i<b2;++i)
                for (long long j=0;j<10;++j)
                {
                    long long rem=(i*(b2%MOD)%MOD*10%MOD+j*(b2%MOD)%MOD+calc(i,left))%MOD;
                    rem=(rem+MOD)%MOD;
                    int key=(rem*(b1%MOD)%MOD);
                    ++li[key];
                }
        }
        printf("prep finished\n");
        for (long long i=b1/10;i<b1;++i)
        {
            long long key=(i%MOD*(b3%MOD)%MOD+calc(i,chunk))%MOD;
            key=(key+MOD)%MOD;
            key=(MOD-key)%MOD;
            if (li.find((int)key)!=li.end())
            {
                //printf("%lld %lld\n",i,key);
                long long temp=li[(int)key];
                ans+=temp;
            }
        }
        printf("%lld finished, ans=%lld\n",len,ans);
    }
    printf("%lld\n",ans);
    return 0;
}
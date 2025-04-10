#include <iostream>

using namespace std;
const uint64_t p=1000000009ULL;
const uint64_t n=1000000000000000000ULL;

class Mat2x2
{
    public:
    uint64_t e11,e12,e21,e22;

    Mat2x2(uint64_t a,uint64_t b,uint64_t c,uint64_t d)
    {
        e11=a;
        e12=b;
        e21=c;
        e22=d;
    }
};

Mat2x2 multmod(Mat2x2 a,Mat2x2 b, uint64_t mod)
{
    Mat2x2 result(0,0,0,0);
    result.e11=(a.e11*b.e11+a.e12*b.e21)%mod;
    result.e12=(a.e11*b.e12+a.e12*b.e22)%mod;
    result.e21=(a.e21*b.e11+a.e22*b.e21)%mod;
    result.e22=(a.e21*b.e12+a.e22*b.e22)%mod;
    return result;
}

Mat2x2 expmodmat(Mat2x2 base, uint64_t exp, uint64_t mod)
{
    if(exp==1) return base;
    Mat2x2 x=expmodmat(base,exp/2,mod);
    Mat2x2 result = multmod(x,x,mod);
    if(exp%2==1) result=multmod(result,base,mod);
    return result;
}

uint64_t expmod(uint64_t base,uint64_t exp,uint64_t mod)
{
    if(exp==1) return base;
    uint64_t x=expmod(base,exp/2,mod);
    x=x*x%mod;
    if(exp%2==1) x=x*base%mod;
    return x;
}

int main()
{
    Mat2x2 A(1,1,1,0),F(0,0,0,0);
    uint64_t result,num,den,pow2;
    F=expmodmat(A,n,p);
    pow2=expmod(2,n,p);
    num=(pow2*F.e22-1)%p;
    den=pow2*pow2%p+1+p-(pow2*(F.e11+F.e22)%p)%p;
    result=num*expmod(den,p-2,p)%p;
    cout << result << endl;
    return 0;
}
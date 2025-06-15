#include <cstdio>
#include <cmath>
#include <cstring>
#include <algorithm>
const int N=50;
struct Complex{
    long double x,y;
    Complex(long double _x = 0.0, long double _y = 0.0){
        x = _x; y = _y;
    }
    Complex(const Complex &obj)
    {
        x=obj.x;
        y=obj.y;
    }
    Complex operator -(const Complex &b)const{
        return Complex(x - b.x, y - b.y);
    }
    Complex operator +(const Complex &b)const{
        return Complex(x + b.x, y + b.y);
    }
    Complex operator *(const Complex &b)const{
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};

void change(Complex y[],int len){
    int i,j,k;
    for(i = 1, j = len / 2; i < len - 1; i++){
        if(i < j) std::swap(y[i],y[j]);
        k = len / 2;
        while(j >= k){
            j -= k;
            k /= 2;
        }
        if(j < k) j += k;
    }
}
void fft(Complex y[],int len,int on){
    change(y,len);
    for(int h = 2; h <= len; h <<= 1){
        Complex wn(cosl(-on*2*M_PI/h),sinl(-on*2*M_PI/h));
        for(int j = 0; j < len; j += h){
            Complex w(1,0);
            for(int k = j; k < j + h / 2; k++){
                Complex u = y[k];
                Complex t = w * y[k + h / 2];
                y[k] = u + t;
                y[k + h / 2] = u - t;
                w = w * wn;
            }
        }
    }
    if(on == -1){
        for(int i = 0; i < len; i++) y[i].x /= len;
    }
}
const int U=24;
long double x[1<<U],y[1<<U],z1[1<<U];
Complex x1[1<<U],x2[1<<U];
void fft_helper(long double *x,long double *y,const int round)
{
    for (int i=0;i<(1<<U);++i)
        x1[i]=Complex(x[i],0),x2[i]=Complex(y[i],0);
    fft(x1,1<<U,1);
    fft(x2,1<<U,1);
    for (int i=0;i<(1<<U);++i)
        x1[i]=x1[i]*x2[i];
    fft(x1,1<<U,-1);
    for (int i=0;i<(1<<U);++i)
        x[i]=x1[i].x;
}
long double E_fast(const int k=-1,const long double p=0.47,const long double q=0.48,const long double r=0.001)
{
    memset(x,0,sizeof(x));
    memset(y,0,sizeof(y));
    x[2]=p*(1-r),y[2]=p*(1-r);
    x[1]=(1-p-q)*(1-r),y[1]=(1-p-q)*(1-r);
    x[0]=q*(1-r),y[0]=q*(1-r);
    long double ans=p;
    int round=1;
    while (true)
    {
        for (int i=0;i<=round*2;++i)
            z1[i]=x[i];
        fft_helper(x,y,round);
        for (int i=0;i<=round*2;++i)
            x[i+round]+=z1[i];
        fft_helper(y,y,round);
        long double tmp=0;
        for (int i=round*2+1;i<=round*4;++i)
            tmp+=x[i];
        tmp/=(1-r);
        if (fabsl(tmp-ans)<1e-7) break;
        ans=tmp;
        round<<=1;
        printf("round=%d, ans=%.6f\n",round,(double)ans),fflush(stdout);
    }
    return ans;
}
int main()
{
    long double ans=0;
    for (int k=3;k<=N;++k)
    {
        long double temp=E_fast(k,1/sqrtl(k+3),1/sqrtl(k+3)+(long double)1.0/k/k,(long double)1.0/k/k/k);
        printf("%d finished, now=%.6f\n",k,(double)temp),fflush(stdout);
        ans+=temp;
    }
    printf("%.4f\n",(double)ans);
    return 0;
}
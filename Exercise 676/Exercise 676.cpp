#include <bits/stdc++.h>

using namespace std;

const long long N=10000000000000000ll, M=10000000000000000ll, X=500, S=100000000ll;
long long n, ki, k[60];
unsigned long long nu[100][2*X], su[100][2*X];
long long a, b, t[100];


long long sm(long long a, long long b) {
    long long a1=a%S, a2=a/S, b1=b%S, b2=b/S, c=((a1*b2+a2*b1)%S)*S+a1*b1;
    return c;
}

long long solve(long long n, long long m, long long v) {
    long long ki=0;
    for(int i=0;i<100;i++) for(int j=0;j<2*X;j++) nu[i][j]=su[i][j]=0;
    long long p=1, x=0;
    while(2*p<=n+1) {
        x++;
        p*=2;
    }
    nu[0][X+m]=1;
    su[0][X+m]=v;
    for(int i=0;i<x;i++) {
        for(int j=0;j<2*X;j++) {
            nu[i+1][j]=(nu[i+1][j]+nu[i][j])%M;
            su[i+1][j]=(su[i+1][j]+su[i][j])%M;
            if(j+t[i]>=0 && j+t[i]<2*X) {
                nu[i+1][j+t[i]]=(nu[i+1][j+t[i]]+nu[i][j])%M;
                su[i+1][j+t[i]]=(su[i+1][j+t[i]]+su[i][j])%M;
                su[i+1][j+t[i]]=(su[i+1][j+t[i]]+sm(nu[i][j],k[i]))%M;
            }
        }
    }
    ki=su[x][X];
    if(p<n) ki+=solve(n-p, m+t[x], v+p);
    return ki%M;
}


int main()
{
    k[0]=1;
    for(int i=1;i<60;i++) k[i]=2*k[i-1];
    for(int k=3;k<=6;k++) {
        for(int l=1;l<=k-2;l++) {
            a=b=1;
            for(int i=0;i<100;i++) {
                t[i]=a-b;
                a*=2;
                b*=2;
                if((i+1)%k==0) a=1;
                if((i+1)%l==0) b=1;
            }
            ki=(ki+solve(N,0,0))%M;
            cout << "*" << endl;
        }
    }
    cout << ki << endl;
    return 0;
}

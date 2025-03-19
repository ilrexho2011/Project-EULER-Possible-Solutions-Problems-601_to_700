#include <math.h>
#include <stdio.h>
#include <stdlib.h>
typedef long long ll;
ll *pMax, *phi, pN, *prime, pCount=0;

void findPhi(ll n, ll x=1, ll iMax=-1, ll phix=1) {
  if (x==1)
    iMax=pCount-1,phi=new ll[n+1];
  phi[x]=phix;
  for (ll i=0,p; i<=iMax&&x<=n/(p=prime[i]); i++)
    for (ll pkp=1,xik=x*p; xik<=n; pkp*=p,xik*=p)
      findPhi(n,xik,i-1,phix*(p-1)*pkp);
}

int main(int argc, char* argv[]) {
  ll N=(argc<2?1:atoll(argv[1]));

  pN=3000000;//N+2;
  pMax=new ll[pN];pMax[0]=pMax[1]=1;
  prime=new ll[pN];
  for (ll i=2; i<pN; i++)pMax[i]=0;
  for (ll p=2; p<pN; p++)
    if (!pMax[p]) {
      prime[pCount++]=p;
      for (ll kp=p; kp<pN; kp+=p)
        pMax[kp]=p;
    }
  findPhi(pN);

  ll ans=0, nlp=1, nmin=0, k;
  for (k=2; nmin+phi[k]*k/2<=N; k++) nlp+=phi[k], nmin+=phi[k]*k/2;
  printf("nmin=%lld for %lld lattice points, n+d=%lld, F(%lld) ~ %lld\n",nmin,nlp,k-1,N,nlp+(N-nmin)*2/k);
}
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

using LL=long long;

vector<LL> P;

LL cubefree(int a,LL n){
  LL r=n;
  for(;a<P.size() && n/P[a]/P[a]/P[a];++a) r-=cubefree(a+1,n/P[a]/P[a]/P[a]);
  return r;
}

LL isqrt(LL a){
  LL x=max(0ll,(LL)sqrt(1.*a));
  while(x*x>a) --x;
  while((x+1)*(x+1)<=a) ++x;
  return x;
}

LL F(LL N){
  P.clear();
  vector<int> D((int)pow(1.*N,1./3)+10);
  for(LL p=2;p<D.size();++p){
    if(D[p]) continue;
    D[p]=p;
    P.push_back(p);
    for(LL i=p*p;i<D.size();i+=p) D[i]=p;
  }
  auto sqfr=[&](LL t){
    int c=0;
    while(t>1){
      LL p=D[t];
      t/=p;
      if(t%p==0) return 0;
      ++c;
    }
    return c;
  };
  LL ans=0;
  for(LL b=2;b*b*b*4<=N;++b){
    if(!sqfr(b)) continue;
    ans+=isqrt(N/(b*b*b))-1;
  }
  for(LL b=2;b*b*b*b*b*b<=N;++b){
    ans+=cubefree(0,isqrt(N/(b*b*b*b*b*b)))-(D[b]==b);
  }

  return ans;
}

int main(){
  cout<<F(9000000000000000000ll)<<endl;

  return 0;
}
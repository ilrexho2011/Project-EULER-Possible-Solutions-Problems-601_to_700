#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const double EPS = 1e-12;
const double sq2=sqrt(2.);

void grundy(double lim,vector<double>&P,vector<int>&G){
  P.push_back(0);
  P.push_back(1);
  G.push_back(0);
  vector<int> W;
  int cur=0;
  while(P.back()<lim-EPS){
    double mn=1e200;
    ++cur;
    for(double s:{1.,sq2}){
      int jj=P.size()-1;
      for(int i=0;i+1<P.size();++i){
        while(jj>=0 && P[i]+P[jj]+s>P.back()+EPS) --jj;
        for(int j=jj;j>=0 && P[i+1]+P[j+1]+s>P.back()+EPS;--j){
          assert(P[i]+P[j]+s<=P.back()+EPS && P[i+1]+P[j+1]+s>P.back()+EPS);
          int g=G[i]^G[j];
          while(W.size()<=g) W.push_back(0);
          W[g]=cur;
          mn=min(mn,P[i+1]+P[j+1]+s);
        }
        if(P[i+1]+s>P.back()) mn=min(mn,P[i+1]+s);
      }
    }
    assert(mn>P.back());
    int g=0;
    while(W[g]==cur) ++g;
    if(g==G.back()) P.back()=mn;
    else{
      P.push_back(mn);
      G.push_back(g);
    }
  }
}

double E(double L,const vector<double>&P,const vector<int>&G){
  double ans=0;
  vector<char> W(1);
  for(double s:{1.,sq2}){
    vector<pair<double,int>> evs;
    int jj=(int)P.size()-2;
    for(int i=0;i+1<P.size();++i){
      while(jj>=0 && P[i]+P[jj]+s>L) --jj;
      for(int j=jj;j>=0 && P[i+1]+P[j+1]+s>L;--j){
        assert(P[i]+P[j]+s<=L && P[i+1]+P[j+1]+s>L);
        double x=max(P[i],L-s-P[j+1]);
        double y=min(P[i+1],L-s-P[j]);
        assert(y>x-EPS);
        if(y<=x) continue;
        evs.emplace_back(x,G[i]^G[j]);
        evs.emplace_back(y,~(G[i]^G[j]));
      }
    }
    sort(evs.begin(),evs.end());
    assert(fabs(evs[0].first)<EPS);
    assert(fabs(evs.back().first-L+s)<EPS);
    for(int i=0;i+1<evs.size();++i){
      int g=evs[i].second;
      if(g<0) W.at(~g)=0;
      else{
        while(W.size()<=g) W.push_back(0);
        W[g]=1;
      }
      if(W[0]) ans+=(evs[i+1].first-evs[i].first)/(L-s)*.5*L;
    }
  }
  return ans;
}

double F(int A,int B){
  vector<double> P;
  vector<int> G;
  grundy(B,P,G);
  double ans=max(E(A,P,G),E(B,P,G));
  for(int x=0;x<=B;++x) for(int y=0;x+y*sq2<=B;++y) if(x+y*sq2>=A) ans=max(ans,E(x+y*sq2,P,G));
  return ans;
}

int main(){
  cout.precision(12);
  cout<<F(200,500)<<endl;
  return 0;
}
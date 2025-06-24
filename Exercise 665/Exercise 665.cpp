#include <iostream>
#include <utility>
#include <set>
#include <climits>

using namespace std;

typedef pair<int,int> interval;
void insert_point(set<interval> &inter, int n) {
	interval i{n,n};
	set<interval>::iterator p2=inter.lower_bound(i);
	auto p1=p2;
	if (p1!=inter.begin()) p1--;
	if (p2!=inter.begin() and p1->second==n-1) {
		i.first=p1->first;
		inter.erase(p1);
	}
	if (p2!=inter.end() and p2->first == n+1) {
		i.second=max(p2->second,i.second);
		inter.erase(p2);
	}
	inter.insert(i);
}

interval find_point(set<interval> &inter, int n) {
	auto p = inter.lower_bound({n,INT_MAX});
	if (p==inter.begin()) return {INT_MAX,INT_MAX};
	p--;
	if (p->second<n) return {INT_MAX,INT_MAX};
	return *p;
}

void print(set<interval> &inter) {
	for (auto &p : inter) cout<<"("<<p.first<<","<<p.second<<") ";
	cout<<endl;
}

const int M = 10000000;

int main() {
	long sum = 0;
	set<interval> A,AB,A2B;
	insert_point(A,0);
	insert_point(AB,0);
	insert_point(A2B,0);
	for (int m=1;m<=M;m++) {
		//if (m%1000==0) cout<<m<<endl;
		for (int a=1;a<=m/2;a++) {
			interval i;
			if (i=find_point(A,a), i.first!=INT_MAX) {
				a = i.second;
				continue;
			}
			if (i=find_point(A,m-a), i.first!=INT_MAX) {
				a = m-i.first;
				continue;
			}
			if (i=find_point(AB,m-2*a), i.first!=INT_MAX) {
				a = (m-i.first)/2;
				continue;
			}
			if (i=find_point(A2B,m-3*a), i.first!=INT_MAX) {
				a = (m-i.first)/3;
				continue;
			}
			if (i=find_point(A2B,3*a-2*m), i.first!=INT_MAX) {
				a = (2*m+i.second)/3;
				continue;
			}
			
			//cout<<a<<","<<m-a<<endl;
			sum+=m;
			insert_point(A,a);
			insert_point(A,m-a);
			insert_point(AB,m-2*a);
			insert_point(A2B,m-3*a);
			insert_point(A2B,3*a-2*m);
		}
	}
	cout<<sum<<endl;
}

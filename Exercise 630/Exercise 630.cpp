#include <bits/stdc++.h>
typedef long long LL;
using namespace std;

int main(){
	int N = 2500;
	vector<LL> s;
	vector<LL> t;
	vector<pair<LL,LL> > pts;
	vector<pair<pair<LL,LL>, LL> > lines;
	for(int k = 0; ; k++){
		if(k == 0){
			s.push_back(290797);
		} else {
			s.push_back((s[k-1]*s[k-1]) % 50515093);
		}
		t.push_back(s[k] % 2000);
		if(k % 2 == 0 && k > 0){
			pts.push_back({t[k-1], t[k]});
		}
		if(pts.size() >= N){
			break;
		}
	}
	for(int i = 0; i < pts.size(); i++){
		for(int j = 0; j < i; j++){
			pair<LL,LL> p1 = pts[i];
			pair<LL,LL> p2 = pts[j];
			if(p1 == p2) assert(false);
			pair<LL,LL> p3 = {p2.first-p1.first, p2.second-p1.second};
			LL g = abs(__gcd(p3.first, p3.second));
			if(p3.first < 0 || (p3.first == 0 && p3.second < 0)) g = -g;
			p3.first /= g; p3.second /= g;
			LL q = p2.second * p3.first - p3.second * p2.first;
			lines.push_back({p3, q});
		}
	}
	sort(lines.begin(), lines.end());
	vector<pair<pair<LL,LL>, LL> > distinct;
	for(int a = 0; a < lines.size(); a++){
		if(a > 0 && lines[a] == lines[a-1]) continue;
		distinct.push_back(lines[a]);
	}
	cout << distinct.size() << endl;
	distinct = lines;
	map<pair<LL,LL>, LL> cnt;
	LL tot = 0;
	LL ans = 0;
	for(int a = 0; a < distinct.size(); a++){
		cnt[distinct[a].first]++;
		tot++;
		ans += tot - cnt[distinct[a].first];
	}
	cout << distinct.size() << " " << ans*2 << endl;
}
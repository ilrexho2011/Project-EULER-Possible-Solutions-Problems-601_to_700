#include <bits/stdc++.h>
using namespace std;
using ll=long long;
const int nax=10*1000*1007;
using ld=long double;
const ld phi=(1+sqrt(5.0))/2;

struct suffix_automaton {
	vector<map<char,int>> edges;
	vector<int> link, length;
	int last;
	suffix_automaton(string s) {
		edges.push_back(map<char,int>());
		link.push_back(-1);
		length.push_back(0);
		last = 0;
		for (int i=0; i<(int)s.size(); i++) {
			edges.push_back(map<char,int>());
			length.push_back(i+1);
			link.push_back(0);
			int r = edges.size() - 1;
			int p = last;
			while (p >= 0 && !edges[p].count(s[i])) {
				edges[p][s[i]] = r;
				p = link[p];
			}
			if (p != -1) {
				int q = edges[p][s[i]];
				if (length[p] + 1 == length[q]) {
					link[r] = q;
				}
				else {
					edges.push_back(edges[q]);
					length.push_back(length[p] + 1);
					link.push_back(link[q]);
					int qq = edges.size()-1;
					link[q] = link[r] = qq;
					while (p >= 0 && edges[p][s[i]] == q) {
						edges[p][s[i]] = qq;
						p = link[p];
					}
				}
			}
			last = r;
		}
	}
};

int n;
int a[nax];
int b[nax];
int c[nax];

int m;
suffix_automaton X=suffix_automaton("");
int was[nax];
int occ[nax];
int longest[nax];

void dfs(int v)
{
	if (was[v])
		return;
	was[v]=1;
	for (auto i : X.edges[v])
	{
		dfs(i.second);
		occ[v]+=occ[i.second];
	}
}

int main()
{
	scanf("%d", &n);
	for (int i=1; i<n; i++)
	{
		if (i&1)
			a[i]=1-a[i/2];
		else
			a[i]=a[i/2];
	}
	for (int i=0; i<n; i++)
		b[i]=llround(floor((i+1)/phi))-llround(floor(i/phi));
	for (int i=0; i<n; i++)
		c[i]=a[i]+b[i]-2*a[i]*b[i];
	string s="";
	for (int i=0; i<n; i++)
		s+=(char)('0'+c[i]);
	X=suffix_automaton(s);
	m=X.edges.size();
	int v=0;
	for (char i : s)
		v=X.edges[v][i];
	while(v)
	{
		occ[v]++;
		v=X.link[v];
	}
	dfs(0);
	for (int i=1; i<m; i++)
		longest[occ[i]]=max(longest[occ[i]], X.length[i]);
	int tmp=0;
	ll res=0;
	for (int i=n; i; i--)
	{
		tmp=max(tmp, longest[i]);
		res+=tmp;
	}
	printf("%lld\n", res);
	return 0;
}
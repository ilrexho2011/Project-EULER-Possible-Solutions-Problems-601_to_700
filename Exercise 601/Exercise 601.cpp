#include<bits/stdc++.h>
using namespace std;

#define int long long
#define for2(a,b,c) for(int a = b; a < c; a++)

int32_t main()
{
	int ans = 0;
	for(int k = 1; k <= 31; k ++)
	{
		int mm = 1ll<<(2*k);
		int lcm = 1;
		for(int j= 1; j <= k; j ++)lcm = lcm*j/__gcd(lcm,j);
		int t = 1;
		while(1)
		{
			if( t*lcm+1 >= mm) break;
			if( (t*lcm)%(k+1) != 0 ) ans ++;
			t ++;
		}
	}
	cout << ans << endl;
	return 0;
}

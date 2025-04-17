#include <vector>
#include <iostream>
using namespace std;
const int mod = 1000000007;
int solve(int n) {
	int s = 1;
	while(s < n) s *= 2;
	vector<int> grundy(n + 1); // grundy number if m = 3
	vector<vector<vector<bool> > > dp(n + 1, vector<vector<bool> >(4, vector<bool>(s)));
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= 3; ++j) {
			for(int k = 0; k < s; ++k) {
				for(int l = 1; l < i; ++l) {
					if(dp[i - l][j - 1][k ^ grundy[l]]) {
						dp[i][j][k] = true;
					}
				}
			}
		}
		while(true) {
			bool ok = false;
			for(int j = 2; j <= 3; ++j) {
				if(dp[i][j][grundy[i]]) ok = true;
			}
			if(!ok) break;
			++grundy[i];
		}
		dp[i][1][grundy[i]] = true;
	}
	vector<vector<int> > comb2(n + 1, vector<int>(s, 0)); comb2[0][0] = 1;
	vector<vector<int> > comb3(n + 1, vector<int>(s, 0)); comb3[0][0] = 1;
	vector<vector<int> > comb4(n + 1, vector<int>(s, 0)); comb4[0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = i; j <= n; ++j) {
			for(int k = 0; k < s; ++k) {
				comb2[j][k] += comb2[j - i][k ^ ((i - 1) % 2)], comb2[j][k] %= mod;
				comb3[j][k] += comb3[j - i][k ^ grundy[i]], comb3[j][k] %= mod;
				comb4[j][k] += comb4[j - i][k ^ (i - 1)], comb4[j][k] %= mod;
			}
		}
	}
	int sum = 0;
	for(int i = 1; i < s; ++i) {
		if(n >= 2) sum += comb2[n][i], sum %= mod;
		if(n >= 3) sum += comb3[n][i], sum %= mod;
		sum = (sum + 1LL * (n >= 3 ? n - 3 : 0) * comb4[n][i]) % mod;
	}
	return sum;
}
int main() {
	int u = clock();
	int ret = solve(200);
	cout << "Answer=" << ret << ", Time=" << 1.0 * (clock() - u) / CLOCKS_PER_SEC << "sec\n";
	return 0;
}
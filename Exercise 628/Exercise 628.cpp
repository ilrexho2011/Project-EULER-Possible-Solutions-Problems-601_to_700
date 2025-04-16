#include <iostream>
#include <time.h>

using namespace std;

int main() {

	clock_t time_start = clock();

	long long MAX = 100000000LL;
	long long MOD = 1008691207LL;

	long long j = 1;
	long long sum = 1;
	long long i = 0;
	long long res = 0;

	for(i=1;i<=MAX-1;i++) {
		j *= i;
		j %= MOD;
		sum += j;
		sum %= MOD;
	}
	res = ((MAX-3) * sum + 2) % MOD;
	cout << res << "\n";



	clock_t time_end = clock();

	cout << ((double)(time_end - time_start))/CLOCKS_PER_SEC << "\n";
	return 0;
}

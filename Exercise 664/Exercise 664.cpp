#include <iostream>
#include <cmath>
using namespace std;

const long long n = 1234567;
const double phi = (1+sqrt(5.l))/2;

bool test(long long k){
	// 3 * sum_{d=0}^\infty d^n/phi^(d+k-1) > 1 ?
	// *3 because of the 2 rows above and below the midline
	double sum = 0;
	long long U = n * log(n);
	for(int d = 1; d < U; ++d){
		sum += exp(n * log(d) - (d+k-1) * log(phi));
		if(3*sum >= 1) return true;
	}
	return false;
}

int main(){
	long long h = n*log(n)*log(n);
	long long l = 1;
	while(l < h){
		auto m = (l+h+1)/2;
		if(test(m)) l = m;
		else h = m-1;
	}
	cout << "Ans: " << l << endl;
}
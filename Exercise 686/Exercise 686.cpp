#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

struct timer
{
   double t;
   timer() { t=clock(); }
   ~timer() { printf("runtime %.3f secs\n", (clock()-t)/CLOCKS_PER_SEC); }
};

typedef long long int64;
typedef unsigned long long uint64;
typedef unsigned int uint;
typedef unsigned char uint8;
/*
18: p/q=59632978/198096465
[18, 414002815, 414699435] fark=696620
*/
const int N=678910;
const int64 a=414002815, b=414699435, p=59632978, q=198096465, NT=b-a+1;
int64 v[NT];
int64 pe686()
{
	int64 i=NT;
/*
? bezout(59632978,-198096465)
%10 = [51132157, 15392313, 1]
? 51132157*(414699435+1)%198096465
%11 = 75285262
*/
	int64 e=75285262;
	while (--i>=0)
	{
		e-=51132157;
		//e%=q;
		if (e<0) e+=q;
		v[i]=e;
	}
	std::sort(&v[0], &v[NT]);
	return v[N-1];
}
int main(int argc, char**argv)
{
   timer t;
   printf("%lld\n",pe686());
   return 0;
}

#include <stdio.h>
#include <time.h>
#include <map>

typedef unsigned int uint;

//#define SMALL
#ifdef SMALL
static const uint n = 2;
static const uint NTURNS = 100; // 5.673651 (0 sec)
#else
static const uint n = 6;
static const uint NTURNS = 750; // 50.317928 (19 sec)
#endif

static double INF = 1e300;

static double dfs (uint cards, uint nturns)
{

	if (nturns>=NTURNS)
		return INF;

	typedef std::pair<uint,uint> HASH;
	static std::map<HASH,double> cache;
	HASH hash (cards, nturns);
	if (cache.count (hash))
		return cache[hash];

	if (cards==0)
		return nturns;

	double sum = 0;
	uint num = 0;
	for (uint i=1; i<=n; i++) {
		for (uint j=i; j<=n; j++) {

			double evmin = INF;

			// Check greedy options:
			bool greedy[3];
			memset (greedy, 0, sizeof (greedy));
			bool any = false;
			if (cards & (1<<(i-1))) {
				greedy[0] = true;
				any = true;
			}
			if (j!=i && (cards & 1<<(j-1))) {
				greedy[1] = true;
				any = true;
			}
			if (cards & (1<<(i+j-1))) {
				greedy[2] = true;
				any = true;
			}

			// Option 1:
			if (!any || greedy[0]) {
				cards ^= (1<<(i-1));
				double ev1 = dfs (cards, nturns+1);
				if (ev1<evmin)
					evmin = ev1;
				cards ^= (1<<(i-1));
			}

			// Option 2:
			if (!any || greedy[1]) {
				cards ^= (1<<(j-1));
				double ev2 = dfs (cards, nturns+1);
				if (ev2<evmin)
					evmin = ev2;
				cards ^= (1<<(j-1));
			}

			// Option 3:
			if (!any || greedy[2]) {
				cards ^= (1<<(i+j-1));
				double ev3 = dfs (cards, nturns+1);
				if (ev3<evmin)
					evmin = ev3;
				cards ^= (1<<(i+j-1));
			}

			if (evmin!=INF) {
				if (j==i) {
					sum += evmin;
					num++;
				} else {
					sum += 2*evmin;
					num+=2;
				}
			}
		}
	}
	return cache[hash] = sum/num;
}

void main ()
{
	uint start = time (NULL);
	uint cards = (1<<(2*n))-1;
	double ev = dfs (cards, 0);
	printf ("ev = %f\n", ev); // ev = 50.317928
	printf ("%d sec\n", time(NULL)-start); // 19 sec
}
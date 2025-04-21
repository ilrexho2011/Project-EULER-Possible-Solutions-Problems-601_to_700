#include <stdio.h>
#include <time.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <unordered_map>

typedef unsigned int uint;
typedef unsigned long long ull;

// Prime sieve:
extern uint *Sieve (uint pmin, uint pmax, uint *np=NULL);

// Problem size:
static const uint k = 7;

// Selected prime indices in dfs2() function:
static uint ip[k];

//static const double N = 1e19; // 996727181 (9.9673e-11) // 4 sec
//static const double N = 1e20; // 9996165932 (9.9962e-11) // 40 sec
//static const double N = 1e21; // 100066452578 (1.0007e-10) // 190 sec
//static const double N = 1e22; // 1001033177951 (1.0010e-10) // 1204 sec
static const double N = 1e23; // 10011598040746 (1.0012e-10) // 12157 sec

// Prime range and log of primes:
static uint PMAX = 1e8;
static uint np;
static double *logp;

// Work in log space:
static const double logN = log(N);

// Solution count:
static ull numdfs = 0;

// Lucy_Hedgehog implementation for counting primes below N:
// https://gist.github.com/AdamStelmaszczyk/a6661e53e34bbf8b10af0fa5a5e97395:
static ull lucyh (ull n)
{
	std::vector<ull> V;
	std::unordered_map<ull,ull> S1;
	uint r = (uint) sqrt ((double)n);
	for (uint i=1; i<=r; i++)
		V.push_back (n/i);
	for (uint i=V.back ()-1; i>0; i--)
		V.push_back (i);
	for (uint i=0; i<V.size (); i++) {
		const ull v = V[i];
		S1[v] = v-1;
	}
	for (uint p=2; p<=r; p++) {
		if (S1[p] > S1[p-1]) { // i.e. p = prime
			for (uint i=0; i<V.size (); i++) {
				const ull v = V[i];
				if (v < (ull)p*p)
					break;
				S1[v] -= (S1[v/p]-S1[p-1]);
			}
		}
	}
	return S1[n];
}

static void pcount (double pmax, uint imin)
{
	// Above p max, use Lucy's algorithm:
	if (pmax>logp[np-1]) {
		numdfs += lucyh (exp (pmax)) - imin;
		return;
	}

	// Else simple count:
	for (uint i=imin; logp[i]<=pmax; i++) {
		numdfs++;
		if (i==np-1) {
			printf ("Not enough primes\n");
			return;
		}
	}
}

// Monitor largest prime used:
static double logpmax = -1e30;

// Count number of ways to create product below N:
static void dfs (double prod, uint inext)
{
	numdfs++;

	double pmax = logN-prod;
	for (uint i=inext; logp[i]<=pmax; i++) {

		// Update maximum prime needed BEFORE shortcut:
		logpmax = std::max (logpmax, logp[i+1]);

		// Shortcut the calculation:
		if (i>ip[k-1] && logp[i]+logp[i+1]>pmax) {
			pcount (pmax, i);
			return;
		}
		double prod2 = prod+logp[i];
		uint i2 = i+1;
		for (uint j=0; j<k; j++) {
			if (i==ip[j]) {
				i2 = i;
				break;
			}
		}
		dfs (prod2, i2);
	}
}

// Loop over all products of primes squared:
static void dfs2 (uint i, uint imin, double pmin)
{
	if (i==k) {
		dfs (pmin, 0);
		return;
	}
	for (ip[i]=imin; ; ip[i]++) {
		double p = logp[ip[i]];
		double pmin2 = pmin + 2*p;
		double pmin2b = pmin2;
		for (uint j=i+1; j<k; j++) {
			pmin2b += 2*logp[ip[i]+j-i];
		}
		if (pmin2b>logN)
			break;
		dfs2 (i+1, ip[i]+1, pmin2);
	}
}

void main ()
{
	// Obtain primes and their logs:
	uint start = time (NULL);
	uint *primes = Sieve (2, PMAX, &np);
	printf ("np = %d\n", np);
	logp = new double[np];
	for (uint i=0; i<np; i++)
		logp[i] = log ((double)primes[i]);
	delete primes;

	// Recursive calculation:
	dfs2 (0, 0, 0);

	// Report result:
	double inf = numdfs/N;
	printf ("num(%e:%d) = %lld (%.4e)\n", N, k, numdfs, inf);
			// num(1.000000e+23:7) = 10011598040746 (1.0012e-10)
	printf ("pmax = %e\n", exp (logpmax));
	uint sec = time (NULL)-start;
	printf ("%d sec\n", sec); // 12157 sec (3.4 hrs)
}
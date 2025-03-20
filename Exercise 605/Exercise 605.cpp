#include <stdio.h>
#include <string.h> // for memset

typedef unsigned int uint;

static const uint nmax = 8;
static uint n;

static double sum[nmax];

static void dfs (uint r, uint last, double p)
{
	const uint R = 300;
	if (r==R)
		return;

	double sumk = 0;
	for (uint k=0; k<n; k++)
		sumk += sum[k];

	const double EPS = 1e-12;
	if (sumk>1-EPS)
		return;

	uint p1 = (r-1)%n + 1;
	uint p2 = r%n + 1;
	for (uint opt=0; opt<2; opt++) {
		uint win = opt==0 ? p1 : p2;
		if (win==last)
			sum[win-1] += p/2;
		else
			dfs (r+1, win, p/2);
	}
}

static void analyze (uint k)
{
	double dnummin = 1e30;
	uint nummin;
	uint denmin;
	for (uint den=1; den<1e6; den++) {
		uint num = (uint)(sum[k]*den);
		double dnum = sum[k]*den - num;
		if (dnum>0.999) {
			dnum = 1-dnum;
			num++;
		}
		if (dnum<dnummin) {
			dnummin = dnum;
			//printf ("dnum(%d) = %.12f (%lld/%lld)\n", k+1, dnum, num, den);
			nummin = num;
			denmin = den;
		}
	}
	printf ("a(%d) = %d/%d\n", k+1, nummin, denmin);
}

void main ()
{
	for (n=2; n<=nmax; n++) {
		printf ("\n");
		printf ("n=%d:\n", n);
		memset (sum, 0, n*sizeof (double));
		dfs (1, 0, 1);
		for (uint k=0; k<n; k++)
			analyze (k);
	}
}
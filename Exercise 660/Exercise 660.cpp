#include <stdio.h>
#include <string.h> // for memset
#include <time.h>

typedef unsigned int uint;

static const uint NMIN = 9;
static const uint NMAX = 18;

static uint GCD (uint a, uint b) // recursive
{
	return b==0 ? a : GCD (b, a%b);
}

static bool pan (uint a, uint b, uint c, uint ndig)
{
	bool used[NMAX];
	memset (used, 0, sizeof (used));
	while (a) {
		uint digit = a%ndig;
		if (used[digit])
			return false;
		used[digit] = true;
		a/=ndig;
	}
	while (b) {
		uint digit = b%ndig;
		if (used[digit])
			return false;
		used[digit] = true;
		b/=ndig;
	}
	while (c) {
		uint digit = c%ndig;
		if (used[digit])
			return false;
		used[digit] = true;
		c/=ndig;
	}
	for (uint digit=0; digit<ndig; digit++) {
		if (!used[digit])
			return false;
	}
	return true;
}

static uint sum = 0;

static void process (uint ndig)
{
	// Heuristics:
	const uint DT = 3; // 474766783 (xx sec) amax = 40e6
	const uint amax = 40e6; // from observation

	uint t = time (NULL);
	uint t2 = t;
	uint num = 0;
	for (uint m=1; ; m++) {
		for (uint n=1; n<m; n++) {
			if (GCD (m, n)>1)
				continue;
			if (m%3==n%3)
				continue;
			uint a0 = m*m + m*n + n*n;
			uint b0 = 2*m*n + n*n;
			uint c0 = m*m - n*n;
			for (uint k=1; ; k++) {
				t2 = time (NULL);
				if (t2>t+DT)
					return;
				uint a = k*a0;
				if (a>amax)
					break;
				uint b = k*b0;
				uint c = k*c0;
				if (pan (a, b, c, ndig)) {
					num++;
					sum += a;
					printf ("%d. a=%d, b=%d, c=%d\n", num, a, b, c);
					t = time (NULL);
				}
			}
		}
	}
}

void main ()
{
	uint start = time (NULL);
	for (uint ndig=NMIN; ndig<=NMAX; ndig++) {
		printf ("ndig = %d\n", ndig);
		process (ndig);
	}
	printf ("sum = %lld\n", sum); // 474766783
	printf ("%d sec\n", time(NULL)-start); // 56 sec
}
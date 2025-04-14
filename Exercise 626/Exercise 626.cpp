#include <stdio.h>
#include <time.h>
#include <algorithm>
#include <set>

typedef unsigned int uint;

typedef std::set<uint> S;

static const uint n = 4; // 5;

// Define square matrix:
typedef uint mat[n][n];

// Possible permutations:
static const uint nrot = 24; // 120;
static uint perm[nrot][n];

// Possible flips (n factorial):
static const uint nflip = 1U<<n;
static bool comb[nflip][n];

// Define a matrix based on a bitmask:
static void init (mat &a, uint mask)
{
	uint index = 0;
	for (uint i=0; i<n; i++) {
		for (uint j=0; j<n; j++) {
			a[i][j] = mask & (1U<<index) ? 1 : 0;
			index++;
		}
	}
}

// Compute bitmask from matrix:
static uint getmask (const mat &a)
{
	uint mask = 0;
	uint index = 0;
	for (uint i=0; i<n; i++) {
		for (uint j=0; j<n; j++) {
			if (a[i][j])
				mask |= (1U<<index);
			index++;
		}
	}
	return mask;
}

// Row permutation:
static void rperm (mat &a, uint iperm)
{
	mat b;
	for (uint j=0; j<n; j++) {
		for (uint i=0; i<n; i++) {
			b[i][j] = a[perm[iperm][i]][j];
		}
	}
	for (uint i=0; i<n; i++)
		for (uint j=0; j<n; j++)
			a[i][j] = b[i][j];
}

// Column permutation:
static void cperm (mat &a, uint iperm)
{
	mat b;
	for (uint i=0; i<n; i++) {
		for (uint j=0; j<n; j++) {
			b[i][j] = a[i][perm[iperm][j]];
		}
	}
	for (uint i=0; i<n; i++)
		for (uint j=0; j<n; j++)
			a[i][j] = b[i][j];
}

// Row flips:
static void rflip (mat &a, uint iflip)
{
	for (uint j=0; j<n; j++) {
		for (uint i=0; i<n; i++) {
			if (comb[iflip][i])
				a[i][j] = 1 - a[i][j];
		}
	}
}

// Column flips:
static void cflip (mat &a, uint iflip)
{
	for (uint i=0; i<n; i++) {
		for (uint j=0; j<n; j++) {
			if (comb[iflip][j])
				a[i][j] = 1 - a[i][j];
		}
	}
}

// Set of all possible sets:
static std::set<S> ss;

// Compute set of transformations of given matrix:
static void getS (uint mask)
{
	S s;
	for (uint irotr=0; irotr<nrot; irotr++) {
		for (uint irotc=0; irotc<nrot; irotc++) {
			for (uint iflipr=0; iflipr<nflip; iflipr++) {
				for (uint iflipc=0; iflipc<nflip; iflipc++) {

					// Generate matrix and transform:
					mat a;
					init (a, mask);
					rperm (a, irotr);
					cperm (a, irotc);
					rflip (a, iflipr);
					cflip (a, iflipc);
					uint mask2 = getmask (a);

					// Check if already in set of sets:
					for (auto it=ss.begin (); it!=ss.end (); it++) {
						const S &s2 = *it;
						if (s2.count (mask2)) {
							return;
						}
					}

					// Add to current set:
					s.insert (mask2);
				}
			}
		}
	}

	// Add set to set of sets:
	ss.insert (s);
}

void main ()
{
	// Timer:
	uint start = time (NULL);

	// Load the possible permutations:
	uint p[n];
	for (uint i=0; i<n; i++)
		p[i] = i;
	uint irot = 0;
	do {
		memcpy (perm[irot], p, n*sizeof (uint));
		irot++;
	} while (std::next_permutation (p, p+n));

	// Load the possible flips:
	for (uint iflip=0; iflip<nflip; iflip++) {
		for (uint i=0; i<n; i++) {
			comb[iflip][i] = (bool)(iflip & (1U<<i));
		}
	}

	// Try all possible matrices:
	for (uint mask=0; mask<(1U<<(n*n)); mask++) {
		printf ("mask = %d (%d)\n", mask, (uint)ss.size ());
		getS (mask);
	}

	// Size of set of sets:
	printf ("ss.size ()=%d\n", (uint)ss.size ()); // 12
	uint sec = time (NULL)-start;
	printf ("%d sec\n", sec); // 7 sec
}
#include <stdio.h>
#include <time.h>
#include <vector>
#include <algorithm>

typedef unsigned int uint;
typedef unsigned long long ull;
typedef long long sll;

struct BE {
	ull base;
	uint expo;
};

// Defined externally:
extern void init_factorize (ull nmax);
extern std::vector<BE> get_pfactors (ull n);
extern std::vector<ull> get_factors (ull n, bool dummy=false);
extern bool IsSquare (ull n);

static const ull N = 1e18;
// cfs.size = 1037561
// num(2) = 1985353
// num(3) = 669
// num(4) = 30
// num(5) = 10
// num(6) = 1
// num(7) = 2

static std::vector<ull> cfs;

static ull mypow (uint base, uint expo)
{
	ull prod = 1;
	for (uint i=0; i<expo; i++)
		prod *= base;
	return prod;
}

static uint num_range (uint i, ull cf)
{
	while (i>0 && cfs[i-1]==cf)
		i--;
	uint num = 1;
	while (i+1<cfs.size () && cfs[i+1]==cf) {
		i++;
		num++;
	}
	return num;
}

static uint binsearch (uint &iminstart, ull cf)
{
	if (cfs[iminstart]==cf)
		return num_range (0, cf);
	if (cfs.back ()==cf)
		return num_range (cfs.size ()-1, cf);
	uint imin = iminstart;
	uint imax = cfs.size ()-1;
	while (imax>imin) {
		uint ictr = (imin+imax)/2;
		if (ictr==imin)
			return 0;
		if (cfs[ictr]<cf) {
			imin = ictr;
			iminstart = imin;
		} else if (cfs[ictr]>cf) {
			imax = ictr;
		} else {
			return num_range (ictr, cf);
		}
	}
	return 0;
}

static uint check_ssq (ull cf) // from trizen
{
	std::vector<BE> pfac = get_pfactors (cf);
	uint B = 1;
	for (uint i=0; i<pfac.size (); i++) {
		if (pfac[i].base%4==3 && pfac[i].expo%2==1)
			return 0;
		if (pfac[i].base%4==1)
			B *= (pfac[i].expo+1);
	}
	return B/2;
}

static uint check_scu (ull cf) // from trizen
{
	uint count = 0;
	std::vector<ull> facs = get_factors (cf);
	for (uint i=0; i<facs.size (); i++) {
		ull d = facs[i];
		ull d2 = d*d;
		ull l = d2 - cf/d;
		if (l%3)
			continue;
		sll t = (sll)d2 - (sll)4*(l/3);
		ull d3 = d2*d;
		if (d3>=cf && d3<=4*cf && l>=3 && t>0 && IsSquare (t))
			count++;
	}
	return count;
}

void main ()
{
	uint start = time (NULL);
	init_factorize (N);

	// Collect possible rhs values:
	for (uint f=3; ; f++) {
		printf ("f=%d\n", f);
		bool any = false;
		for (uint c=2; ; c++) {
			ull cf = mypow (c, f);
			if (cf>N)
				break;
			cfs.push_back (cf);
			any = true;
		}
		if (!any)
			break;
	}

	// Sort to allow binary search:
	std::sort (cfs.begin (), cfs.end ());
	printf ("cfs.size = %d\n", cfs.size ());

	// Possible sums of two squares:
	uint num = 0;
	for (uint i=0; i<cfs.size (); i++) {
		num += check_ssq (cfs[i]);
	}
	printf ("num(2) = %d\n", num);

	// Possible sums of two cubes:
	uint num3 = 0;
	for (uint i=0; i<cfs.size (); i++) {
		num3 += check_scu (cfs[i]);
	}
	printf ("num(3) = %d\n", num3);
	num += num3;

	// e>3:
	for (uint e=4; e<10; e++) {  // limit to prevent overflow
		uint ne = 0;
		for (uint b=2; ; b++) {
			bool any = false;
			ull be = mypow (b, e);
			uint iminstart = 0;
			for (uint a=1; a<b; a++) {
				ull ae = mypow (a, e);
				ull cf = ae + be;
				if (cf>N)
					break;
				uint dnum = binsearch (iminstart, cf);
				num += dnum;
				ne += dnum;
				any = true;
			}
			if (!any)
				break;
		}
		printf ("num(%d) = %d\n", e, ne);
	}
	printf ("num = %d\n", num); // 1986065
	uint sec = time(NULL)-start;
	printf ("%.1f min\n", sec/60.); // 8.7 min
}
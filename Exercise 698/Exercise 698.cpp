#include <stdio.h>
#include <set>

typedef unsigned int uint;
typedef unsigned long long ull;

// Defined externally:
extern ull modpow (ull a, ull b, ull mod, bool usemulmod=false);

static const uint nmax = 40;
static ull bin[nmax+1][nmax+1];

static void set_binom ()
{
	for (uint n=0; n<=nmax; n++) {
		for (uint m=0; m<=n; m++) {
			bin[n][m] = (m==0 || m==n ? 1 : bin[n-1][m-1]+bin[n-1][m]);
		}
	}
}

static uint binom (uint n, uint m)
{
	return bin[n][m];
}

static bool is123 (uint num)
{
	if (num==0) return true;
	if (num==1) return true;
	if (num==2) return true;
	if (num==3) return true;
	if (num==11) return true;
	if (num==12) return true;
	if (num==13) return true;
	if (num==21) return true;
	if (num==22) return true;
	if (num==23) return true;
	if (num==31) return true;
	if (num==32) return true;
	if (num==33) return true;
	return false;
}

static const uint NDIG = 38;
static uint dig[NDIG];
static uint ndig;

static ull getcount (uint num[3])
{
	printf ("   getcount called with %d %d %d\n", num[0], num[1], num[2]);

	// Group already-set digits:
	uint nd[3] = {0, 0, 0};
	for (uint idig=0; idig<ndig; idig++) {
		nd[dig[idig]-1]++;
	}

	// Ways:
	ull count = 0;
	if (is123 (num[0]+nd[0]) && is123 (num[1]+nd[1]) && is123 (num[2]+nd[2]))
		 count++;
	if (is123 (num[0]+nd[0]) && is123 (num[2]+nd[1]) && is123 (num[1]+nd[2]))
		 count++;
	if (is123 (num[1]+nd[0]) && is123 (num[0]+nd[1]) && is123 (num[2]+nd[2]))
		 count++;
	if (is123 (num[1]+nd[0]) && is123 (num[2]+nd[1]) && is123 (num[0]+nd[2]))
		 count++;
	if (is123 (num[2]+nd[0]) && is123 (num[0]+nd[1]) && is123 (num[1]+nd[2]))
		 count++;
	if (is123 (num[2]+nd[0]) && is123 (num[1]+nd[1]) && is123 (num[0]+nd[2]))
		 count++;
	if (num[0]==num[1] && num[0]==num[2])
		count /= 6;
	else if (num[0]==num[1] || num[0]==num[2] || num[1]==num[2])
		count /= 2;

	uint sum = num[0] + num[1] + num[2];
	count *= binom (sum, num[0]);
	sum -= num[0];
	count *= binom (sum, num[1]);

	printf ("                             count=%lld\n", count);
	return count;
}

static const uint NCOMBO = 6;
static uint combo [NCOMBO][3] = {
	{2, 3, 33},
	{2, 13, 23},
	{3, 3, 32},
	{3, 12, 23},
	{3, 13, 22},
	{12, 13, 13}
};

static std::set<uint> S;

static ull get_count2 (uint icombo)
{
	ull count = 0;
	uint *c = combo[icombo];
	for (uint i0=0; i0<=c[0]; i0++) {
		for (uint i1=i0; i1<=c[1]; i1++) {
			for (uint i2=i1; i2<=c[2]; i2++) {
				if (i0+i1+i2+ndig!=NDIG)
					continue;
				uint hash = 10000*i0 + 100*i1 + i2;
				if (S.count (hash))
					continue;
				else
					S.insert (hash);
				uint num[3] = {i0, i1, i2};
				count += getcount (num);
			}
		}
	}
	return count;
}

static ull get_count ()
{
	S.clear ();
	ull count = 0;
	for (uint icombo=0; icombo<NCOMBO; icombo++) {
		ull count2 = get_count2 (icombo);
		printf ("icombo=%d: %lld\n", icombo, count2);
		count += count2;
	}
	return count;
}

void main ()
{
	set_binom ();

	ull togo = 25465451830845483; // from first program
	togo--;

	for (ndig=1; ndig<=NDIG; ndig++) {
		printf ("\n");
		printf ("number so far: ");
		for (uint idig=0; idig<ndig-1; idig++)
			printf ("%d", dig[idig]);
		printf ("\n");
		printf ("-------------- ndig=%d\n", ndig);
		for (uint d=1; d<=3; d++) {
			printf ("probing digit %d: %d\n", ndig, d);
			dig[ndig-1] = d;
			ull count = get_count ();
			printf ("count = %lld\n", count);
			if (count>togo) {
				printf ("digit %d fixed at %d\n", ndig, d);
				printf ("..........togo at %d digits-->%lld\n", NDIG-ndig, togo);
				break;
			} else {
				togo -= count;
				printf ("..........togo at %d digits-->%lld\n", NDIG-ndig, togo);
			}
		}
	}
	const uint mod = 123123123;
	uint ans = 0;
	const uint ND = NDIG;
	for (uint i=0; i<ND; i++) {
		printf ("%d", dig[i]);
		ans += dig[i]*modpow (10, ND-1-i, mod);
		ans %= mod;
	}
	printf ("\n");
	printf ("ans = %d\n", ans);
}
#include <stdio.h>
#include <time.h>
#include <vector>
#include <map>
#include <algorithm>

typedef unsigned int uint;
typedef unsigned char uchar;

static const uint nr = 13;
static const uint ns = 4;
static const uint n = nr*ns;

static bool isprime[nr+1] = {
	0, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1};

typedef std::vector<uchar> HASH;

static HASH get_hash (uint prev, bool perf[nr], uint nused[nr])
{
	struct ITEM {
		uint i;
		bool perf;
		uint nused;
		bool operator < (const ITEM &a) {
			return nused<a.nused;
		}
	};
	ITEM items[nr];
	for (uint i=0; i<nr; i++) {
		items[i].i = i;
		items[i].perf = perf[i];
		items[i].nused = nused[i];
	}
	std::sort (items, items+nr);
	HASH hash;
	uint prev2 = prev;
	for (uint i=0; i<nr; i++) {
		if (items[i].i==prev)
			prev2 = i;
		uint nhash = items[i].nused;
		if (items[i].perf)
			nhash += ns+1;
		hash.push_back (nhash);
	}
	hash.push_back (prev2);
	return hash;
}

typedef std::pair<double,double> PAIR;

static PAIR dfs (uint ntot, uint prev, uint nused[nr], bool perf[nr])
{
	if (ntot==n) {
		uint nperf = nr;
		for (uint r=0; r<nr; r++) {
			if (!perf[r])
				nperf--;
		}
		return isprime[nperf] ? PAIR (1, 0) : PAIR (0, 1);
	}

	HASH hash = get_hash (prev, perf, nused);
	static std::map<HASH,PAIR> cache;
	if (cache.count (hash))
		return cache[hash];

	PAIR sum (0, 0);
	for (uint cur=0; cur<nr; cur++) {
		if (nused[cur]==ns)
			continue;
		bool perf2[nr];
		memcpy (perf2, perf, sizeof (perf2));
		if (cur==prev)
			perf2[cur] = false;
		uint nused2[nr];
		memcpy (nused2, nused, sizeof (nused2));
		nused2[cur]++;
		PAIR dsum = dfs (ntot+1, cur, nused2, perf2);
		sum.first += dsum.first;
		sum.second += dsum.second;
		if (nused[cur]==0)
			break;
	}
	return cache[hash] = sum;
}

void main ()
{
	uint start = time (NULL);
	uint nused[nr];
	bool perf[nr];
	for (uint r=0; r<nr; r++) {
		nused[r] = 0;
		perf[r] = true;
	}
	PAIR sum = dfs (0, UINT_MAX, nused, perf);
	printf ("p(%d) = %.10f\n", nr, sum.first/(sum.first+sum.second));
			// 0.3285320869
	uint sec = time (NULL) - start;
	printf ("%d sec\n", sec); // 268 sec
}
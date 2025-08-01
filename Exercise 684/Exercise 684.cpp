#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define LIMIT	90
#define BASE	1000000007

long long powMod(long long a, long long n, long long m)
{
	long long bit = 1;
	long long i, result = 1;
	
	i = a % m;
	
	while (bit <= n)
	{
		if (n & bit)
		{
			result *= i;
			result %= m;
		}
		
		bit <<= 1;
		i *= i;
		i %= m;
	}
	
	return result;
}

long long modularInverse(long long a, long long m)
{
	return powMod(a, m - 2, m);
}

long long getSum(long long value)
{
	long long result = 0, res, k;
	int i;
	
	for (i = 1; (i <= 9) && (i <= value); i++)
	{
		k = (value - i) / 9 + 1;
		res = (powMod(10, k, BASE) + BASE - 1) % BASE;
		res = res * modularInverse(9, BASE) % BASE;
		res = (i + 1) * res % BASE;
		result = (result + res) % BASE;
	}
	
	result = (result + BASE - (value % BASE)) % BASE;
	
	return result;
}

long long getSolution(int lim)
{
	long long result = 0, fiba = 0, fibb = 1;
	int i;
	
	for (i = 2; i <= LIMIT; i++)
	{
		fibb = fiba + fibb;
		fiba = fibb - fiba;
		result = (result + getSum(fibb)) % BASE;
	}
	
	return result;
}

int main()
{	
	printf("Solution: %lld\n", getSolution(LIMIT));
	printf("Runtime: %.2f seconds\n\n", (float)clock() / CLK_TCK);
	return 0;
}
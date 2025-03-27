// Problem 612: Friend numbers

void Problem612(int exp10)  // exp10 is log base 10 of n
{
	const int ZERO = 0, NOZR = 1;
	long long int sum, excl = 0, ans, mm = 1000267129, nn = (PowInt(10, exp10, 0)) % mm;
	ans = ((nn - 1) * (nn - 2) / 2) % mm;																// all possible (p, q) with p < q; we will subtract exclusions where p and q share no digits
	long long int*** cts;																				// cts[zz][d][n] is # of numbers of length n using all of d non-zero digits and zero (if zz = 0)
	cts = new long long int**[2];
	cts[ZERO] = new long long int*[10]; cts[NOZR] = new long long int*[10];
	for (int zz = ZERO; zz <= NOZR; zz++)
		for (int nzd = 0; nzd <= 9; nzd++)																// zero them all out to start
		{
			cts[zz][nzd] = new long long int[19];
			for (int i = 0; i < 19; i++) cts[zz][nzd][i] = 0;
		}

	for (int n = 1; n <= 18; n++)																		// construct the cts[zz][d][n] ounts
	{
		cts[NOZR][1][n] = 1;																			// e.g., 11111
		for (int d = 2; d <= 9; d++)
		{
			if (d > n) cts[NOZR][d][n] = 0;
			else
			{
				sum = PowInt(d, n, mm);
				for (int k = 1; k < d; k++) sum = (sum + mm - ((cts[NOZR][k][n] * Combin(d, k)) % mm)) % mm;
				cts[NOZR][d][n] = sum;
			}
		}

		if (n == 1) cts[ZERO][1][n] = 0;
			else cts[ZERO][1][n] = PowInt(2, n - 1, mm) - 1;											// e.g., 1001010 but not 1111111
		for (int d = 2; d <= 9; d++)
		{
			if (d + 1 > n) cts[ZERO][d][n] = 0;
			else
			{
				sum = d * PowInt(d + 1, n - 1, mm);
				for (int k = 1; k <= d; k++)
				{
					sum = (sum + mm - ((cts[NOZR][k][n] * Combin(d, k)) % mm)) % mm;					// remove the ones that had no zeros
					if (k < d) sum = (sum + mm - ((cts[ZERO][k][n] * Combin(d, k)) % mm)) % mm;			// remove the ones that had zeros
				}
				cts[ZERO][d][n] = sum;
			}
		}
	}

	int lft, rgt, zr, this_p, lft_z, rgt_z;
	for (int par = 3; par < 59049; par++)									// Count partitions using base 3 (0 means not used, 1, and 2 are partitions)
	{
		lft = 0; rgt = 0; zr = par % 3;										
		lft_z = NOZR; if (zr == 1) lft_z = ZERO;
		rgt_z = NOZR; if (zr == 2) rgt_z = ZERO;							// set flags for which partition has a zero
		this_p = par / 3;
		while (this_p > 0)												
		{
			if ((this_p % 3) == 1) lft++;									// count the number of non-zero digits in each partition
			else if ((this_p % 3) == 2) rgt++;
			this_p /= 3;
		}																			
		for (int n1 = 1; n1 <= exp10; n1++)
			for (int n2 = 1; n2 <= exp10; n2++)							
				excl = (excl + ((cts[lft_z][lft][n1] * cts[rgt_z][rgt][n2]) % mm)) % mm;			
	}
	if ((excl % 2) == 1) excl += mm;
	excl /= 2;																// we have double counted exclusions
	ans = (ans + mm - excl) % mm;
	cout << "Problem 612: Friend numbers: Answer = " << ans << "\n";
}

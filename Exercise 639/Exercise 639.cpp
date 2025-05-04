#include "stdafx.h"
#include <string>
#include <fstream>
#include <iostream>
#include "math.h"
#include <time.h>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

// Euler Project, problem 639
#include "Classes.h"
const int     MOD  = 1000000007;
const int     MAXK = 1;
const __int64 N    = 1000000000000L;
__int64 totalSum;


int NPRIMES;
int * prime = NULL;
void createTableOfPrimesUpTo(int n) {
   // First part: sieve
   char * primeSieve = new char[n+1];
   primeSieve[0] = primeSieve[1] = 0;
   int i, mult;
   for (i=2; i<=n; i++) primeSieve[i] = 1;
   for (i=2; i*i<=n; i++) {
      if (primeSieve[i]==1) {
         mult = i*i;
         while (mult<=n) {
            primeSieve[mult] = 0;
            mult+=i;
         }
      }
   }
   // second part: create table with primes
   NPRIMES = 0;
   for (i=2; i<=n; i++) {
      if (primeSieve[i]==1) NPRIMES++;
   }
   prime = new int[NPRIMES];
   NPRIMES = 0;
   for (i=2; i<=n; i++) {
      if (primeSieve[i]==1) {
         prime[NPRIMES++] = i;
      }
   }
   delete[] primeSieve;
   cout << "prime[" << NPRIMES-1 << "] = " << prime[NPRIMES-1] << "\n";
}


// Find coefficients so that sum_i=1^n i^e = n*faulhaber[1] + ... + n^(e+1)*faulhaber[n+1]  (mod MOD)
int faulhaber[51][51];
void findFaulhaberCoefficientsMod(int e, int MOD) {
   // write equations for the first n+1 cases
   Matrix<__int64> m(e+1,e+1);
   Vector<__int64> b(e+1);
   Vector<__int64> x(e+1);
   __int64 sum = 0;
   for (int limsum = 1; limsum <= e+1; limsum++) {
      __int64 power = 1;
      for (int i = 0; i <= e; i++) {
         power = (power * limsum) % MOD;
         m(limsum - 1, i) = power;
         if (i == e-1) {
            sum = (sum + power) % MOD;
            b[limsum - 1] = sum;         
         }
      }
   }
   m.solveSystemMod(m, b, x, MOD);
   for (int i = 1; i <= e+1; i++) faulhaber[e][i] = (int)x[i-1];
   faulhaber[0][1] = 0; // this is required in the loops in applyFaulhaberSimultaneous
}
int applyFaulhaber(int nFaulhaber, int n, int MOD) {
   __int64 sum = 0;
   __int64 pow = 1;
   for (int exponent = 1; exponent <= nFaulhaber+1; exponent++) {
      pow = (pow * n) % MOD;
      sum = (sum + faulhaber[nFaulhaber][exponent] * pow) % MOD;
   }
   return (int)sum;
}
void applyFaulhaberSimultaneous(__int64 * sumPowers, __int64 n, int MOD) {
   for (int k = 1; k <= 50; k++) sumPowers[k] = 0;
   __int64 pow = 1;
   for (int exponent = 1; exponent <= 51; exponent++) {
      pow = (pow * n) % MOD;
      for (int k = exponent-1; k <= 50; k++) {
         sumPowers[k] = (sumPowers[k] + faulhaber[k][exponent] * pow) % MOD; // Note: faulhaber[0][1] was set to 0
      }
   }
   return;
}


void explore(int inp, int sign, __int64 product, __int64 * correctionFactor) {
   // inp is the index of the next possible prime to add to the factorization.
   // product is the product of the prime numbers in the factorization.
   // correctionFactor are the 50 correction factors for each value of k. Product of factors (p^2k-p^k) for primes p in the product.
   __int64 nextCorrectionFactor[51];
   int ip = inp;
   int p = prime[ip];
   while ( (product*p)*p <= N) {
      // We can add p to the current factorization.
      __int64 nextProduct = product * p;
      do { // Loop for exponents of primes
         // add p to current factorization with exponent e
         nextProduct = nextProduct * p;
         if (nextProduct > N) break;
         __int64 limit = N / nextProduct;

         // OLD LOOP FOR K; ONE POLYNOMIAL EVALUATED AT A TIME
         /*int limitForCall = (int)(limit%MOD);
         for (int k = 1; k <= 50; k++) {
            __int64 pk = p; for (int i = 1; i < k; i++) pk = (pk * p) % MOD; // pk = p^k
            nextCorrectionFactor[k] = (pk * (((pk-1) * correctionFactor[k]) % MOD)) % MOD;
            int sumpowers = applyFaulhaber(k, limitForCall, MOD);
            totalSum = (totalSum + sign * nextCorrectionFactor[k] * sumpowers) % MOD;
         }*/

         // SIMULTANEOUS EVALUATION OF THE 50 POLYNOMIALS
         __int64 limitForCall = limit % MOD;
         __int64 sumPowers[51];
         applyFaulhaberSimultaneous(sumPowers, limitForCall, MOD);
         __int64 pk = 1; // pk = p^k
         __int64 tempSum = 0;
         for (int k = 1; k <= 50; k++) {
            pk = (pk * p) % MOD;
            nextCorrectionFactor[k] = (((pk * (pk-1)) % MOD) * correctionFactor[k]) % MOD;
            tempSum = (tempSum + nextCorrectionFactor[k] * sumPowers[k]) % MOD;
         }
         totalSum = totalSum + sign * tempSum;

         if (limit >= (__int64)prime[ip+1] * (__int64)prime[ip+1]) {
            explore(ip+1, -sign, nextProduct, nextCorrectionFactor);
         }
      } while (true);
      ip++;
      p = prime[ip];
   }
}


int _tmain(int argc, _TCHAR* argv[]){
   clock_t time0 = clock();

   createTableOfPrimesUpTo(1001000);

   totalSum = 0;
   for (int k = 1; k <= 50; k++) {
      findFaulhaberCoefficientsMod(k, MOD);
      totalSum += applyFaulhaber(k, (int)(N%MOD), MOD);
   }

   __int64 correctionFactor[51]; for (int k = 1; k <= 50; k++) correctionFactor[k] = 1;
   explore(0, -1, 1, correctionFactor);

   cout << "totalSum = " << (((totalSum%MOD)+MOD)%MOD) << "\n";
   cout << "time spent = " << clock() - time0 << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); return 0;
}
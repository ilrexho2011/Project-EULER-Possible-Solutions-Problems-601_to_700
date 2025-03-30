#include <stdio.h>
#include <stdlib.h>

typedef long int ulint;

// build (modulo mod) a sequence x[k], 0<=k<=N defined by the pentagonal recursion
// x[0] = init[0] and x[n] = init[n] + x[n-1]+x[n-2]-x[n-5]-x[n-7]+x[n-12]+...
ulint *pentagonal_recursion(ulint *init, ulint N, ulint mod) 
{  
  ulint n,i,k,sign,inc[2],s,*x;

  x = (ulint *)calloc(N+1,sizeof(ulint));
  x[0] = init[0];
  for (n=1;n<=N;n++) {
    i = 0; k = 1; sign = 1;
    inc[0] = 1; inc[1] = 3;
    s = init[n];
    while (k<=n) {
      s = (s+sign*x[n-k])%mod;
      k += inc[i%2];
      inc[i%2] += 1+(i%2);
      i++;
      if (i%2==0) sign = -sign;
    }
    x[n] = (s+mod)%mod;
  }
  return x;
}

main(int argc, char **argv)
{
  ulint N,i,n,k,*a,*b,*init;
  ulint mod = 1000000007;

  if (argc<2) exit(1);
  sscanf(argv[1],"%ld",&N);

  init = (ulint *)malloc((N+1)*sizeof(ulint));
  init[0] = 1;

  // compute a[n] = number of partition of n into distinct parts
  for (n=1;n<=N;n++) init[n] = 0;
  for (n=1;(i=n*(3*n-1))<=N;n++) init[i] = 1-2*(n&1);
  for (n=1;(i=n*(3*n+1))<=N;n++) init[i] = 1-2*(n&1);
  a = pentagonal_recursion(init,N,mod);

  // compute b[n] = number of partition of n into distinct and odd parts
  for (n=1;n<=N;n++) init[n] = 0;
  for (n=1;(i=8*n*n)<=N;n++) init[i] = 2;
  for (n=1;(i=2*(2*n-1)*(2*n-1))<=N;n++) init[i] = -2;
  b = pentagonal_recursion(init,N,mod);

  // compute partial sums of b
  for (n=1;n<=N;n++) b[n] = (b[n]+b[n-1])%mod;

  // compute total sum
  ulint total = -1;
  for (k=0;k<=N/4;k++) 
    total = (total+a[k]*b[N-4*k])%mod;
  total = (total+mod)%mod;
  printf("%ld\n",total);
}
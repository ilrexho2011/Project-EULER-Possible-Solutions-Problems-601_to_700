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

// Euler Project, problem 637
const int N = 10000000;

int _tmain(int argc, _TCHAR* argv[]){
   clock_t time0 = clock();

   int pow2[20]; pow2[0] = 1; for (int i = 1; i < 20; i++) pow2[i] = 2*pow2[i-1];

   int * f10 = new int[N+1];
   for (int i = 0; i < 10; i++) f10[i] = 0; 
   
   int * f3  = new int[N+1];
   for (int i = 0; i < 3; i++) f3[i] = 0;
   
   int digits10[8]; 
   for (int i = 0; i < 8; i++) digits10[i] = 0;
   digits10[6] = 1; // so that we start at 10
   if (N >= 10000000) f10[10000000] = 1;
   for (int i = 10; i < N; i++) { // observe we miss 10^7 to save time
      f10[i] = 10000;
      for (int comb = 0; comb < 128; comb++) {
         int thisSum = 0;
         int thisBlock = digits10[0];
         for (int digit = 1; digit < 8; digit++) {
            if (comb & pow2[digit-1]) {
               thisBlock = 10*thisBlock + digits10[digit];
            }else{
               thisSum = thisSum + thisBlock;
               thisBlock = digits10[digit];
            }
         }
         thisSum += thisBlock;
         if (f10[thisSum] < f10[i]) f10[i] = f10[thisSum]+1;
      }
      if ((i&65535)==0) cout << "f10(" << i << ") = " << f10[i] << "\n";

      // increase digits10
      digits10[7]++;
      if (digits10[7] == 10) {
         int last = 7;
         do {
            digits10[last] = 0;
            last--;
            digits10[last]++;
         } while (digits10[last] == 10);
      }
   }

   int digits3[15]; 
   for (int i = 0; i < 15; i++) digits3[i] = 0;
   digits3[13] = 1; // so that we start at 3
   for (int i = 3; i <= N; i++) {
     f3[i] = 10000;
      for (int comb = 0; comb < 16384; comb++) {
         int thisSum = 0;
         int thisBlock = digits3[0];
         for (int digit = 1; digit < 15; digit++) {
            if (comb & pow2[digit-1]) {
               thisBlock = 3*thisBlock + digits3[digit];
            }else{
               thisSum = thisSum + thisBlock;
               thisBlock = digits3[digit];
            }
         }
         thisSum += thisBlock;
         if (f3[thisSum] < f3[i]) {
            f3[i] = f3[thisSum]+1;
            if (f3[i]<3) break;
         }
      }
      if (f3[i] >= 3) cout << "f3(" << i << ") = " << f3[i] << "\n";
      if ((i&65535)==0) cout << "f3(" << i << ") = " << f3[i] << "\n";

      // increase digits10
      digits3[14]++;
      if (digits3[14] == 3) {
         int last = 14;
         do {
            digits3[last] = 0;
            last--;
            digits3[last]++;
         } while (digits3[last] == 3);
      }
   }

   __int64 sum = 0;
   for (int i = 1; i <= N; i++) {
      if (f10[i] == f3[i]) {
         //cout << "i = " << i << "\n";
         sum = sum + i;
      }
   }
   cout << "sum = " << sum << "\n";



   delete[] f10; delete[] f3;
   cout << "time spent = " << clock() - time0 << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); return 0;
}
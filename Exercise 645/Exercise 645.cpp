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

// Euler Project, problem 645
#include "Classes.h"

const int D = 10000;
const double dD = D;
HugeDouble * nw00  = new HugeDouble[D+1];
HugeDouble * nw01  = new HugeDouble[D+1];
HugeDouble * nw10  = new HugeDouble[D+1];
HugeDouble * nw11  = new HugeDouble[D+1];
HugeDouble * nnw00 = new HugeDouble[D+1];
HugeDouble * nnw01 = new HugeDouble[D+1];
HugeDouble * nnw10 = new HugeDouble[D+1];
HugeDouble * nnw11 = new HugeDouble[D+1];

int _tmain(int argc, _TCHAR* argv[]){
   clock_t time0 = clock();

   // number of ways to make all days holidays, counting different birthdays
   for (int i = 0; i <= D; i++) nw00[i] = nw01[i] = nw10[i] = nw11[i] = 0.0;
   nw00[0] = 1; // 1 way for first day not being a birthday
   nw11[1] = 1; // 1 way for first day being a birthday
   for (int d = 2; d <= D; d++) { // all days after the first
      nnw00[0] = nnw01[0] = nnw10[0] = nnw11[0] = 0.0;
      for (int b = 1; b <= D; b++) {
         nnw00[b] = nw01[b];
         nnw01[b] = nw01[b-1] + nw00[b-1];
         nnw10[b] = nw11[b];
         nnw11[b] = nw10[b-1] + nw11[b-1];
      }
      HugeDouble * temp;
      temp = nw00; nw00 = nnw00; nnw00 = temp;
      temp = nw01; nw01 = nnw01; nnw01 = temp;
      temp = nw10; nw10 = nnw10; nnw10 = temp;
      temp = nw11; nw11 = nnw11; nnw11 = temp;
   }

   // pdb[b] is the probability that there are exactly b different birthdays at current number of emperors
   double * pdb = new double[D+1];
   for (int ndb = 0; ndb <= D; ndb++) pdb[ndb] = 0;
   pdb[0] = 1.0;

   cout << "computing terms sum(nw)/comb(D,ndb) = prob all holidays if given number of different birthdays\n";
   double * probAHifndb = new double[D+1];
   for (int ndb = 1; ndb <= D; ndb++) {
      HugeDouble sum = nw10[ndb]+nw01[ndb]+nw11[ndb];
      for (int i = 0; i < ndb; i++) {
         sum = (sum * (ndb-i)) / (D-i);
      }
      probAHifndb[ndb] = sum.toDouble();
   }

   int e = 1; // first emperor
   double E = 0; // expectation of all days holidays
   double prevPadh = 0;
   while (true) {
      for (int ndb = D; ndb > 0; ndb--) {
         pdb[ndb] = ((D-ndb+1) * pdb[ndb-1] + ndb * pdb[ndb]) / dD;
      }
      pdb[0] = 0;
      double padh = 0; // probability of all days holidays
      for (int ndb = D/2; ndb <= D; ndb++) { // ndb = number of different birthdays
         if (pdb[ndb] != 0) {
            padh = padh + pdb[ndb] * probAHifndb[ndb];
         }
      }
      E = E + e * (padh - prevPadh);
      prevPadh = padh;
      printf("e=%7d E=%12.4f\n", e, E);
      e++; // next emperor
   }

   cout << "time spent = " << clock() - time0 << " ms\n"; cout << "press any key to end\n"; char cinget; cin.get(cinget); return 0;
}
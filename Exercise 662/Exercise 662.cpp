#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include <set>
#include "point.h"

using namespace std;

long F(long x, long y);

const long N = 10000;
const long modulo = 1000000007;

vector<Point> Delta;
vector<vector<long> > Ft(N+1, vector<long>(N+1,-1));

int main()
{
   string ordre = "clear";
   system(ordre.c_str());
   long t_deb = clock();


   set<long> Fibo;
   long f0(1), f1(2);
   while (f0 * f0 <= 2 * N * N)
   {
       Fibo.insert(f0*f0);
       long f2 = f0 + f1;
       f0 = f1; f1 = f2;
   }


   set<long>::iterator it;
   for(long x = 0; x <= N; x++)
   {
       for (long y = x; y <= N; y++)
       {
           it = Fibo.find(x * x + y * y);
           if ( it != Fibo.end())
               Delta.push_back(Point(x,y));
       }
   }

   cout << "pe662 : " << F(N,N) << endl;

   cout << "temps : " << (clock() - t_deb) * 1e-6 << endl;
   char quitte; cin >> quitte;
   return 0;
}

long F(long x, long y)
{
    if (x > y) {long temp = x; x = y; y = temp;}
    if (Ft[x][y] >= 0) return Ft[x][y];
    if (x == 0 and y == 0) return 1;
    long nbChemins = 0;
    for (auto P : Delta)
    {
        long dx = x - P.x, dy = y- P.y;

        if (dx >= 0 and dy >= 0)
        {
            long nbc = F(dx, dy);
            if (nbc != 0) nbChemins = (nbChemins + F(dx, dy)) % modulo ;
        }
        dx = x - P.y; dy = y - P.x;
        if (dx >= 0 and dy >= 0)
        {
            long nbc = F(dx, dy);
            if (nbc != 0) nbChemins = (nbChemins + F(dx, dy)) % modulo ;
        }
    }
    Ft[x][y] = nbChemins;
    return nbChemins;
}

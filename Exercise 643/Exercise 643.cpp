#include <iostream>
#include <cmath>
#include <vector>
#include <map>

using namespace std;

const long modulo = 1000000007;
const long N = 100000000000L;
const long L = 10000000L;
vector<long> v(L+1);
map <long,long> cache;

long isqrt(long n);
void fill_v();
long Phi(long n);
long rem ( long a, long b);

int main()
{  

    long deb = clock();
    fill_v();

    long somme = 0;
    long puiss = 2;
    while (puiss <= N)
    {
        somme = rem(somme + rem(Phi(N/puiss), modulo) - 1, modulo);
        puiss *= 2;
    }

    cout << "pe643 : " << somme << endl;

    cout << "temps : " <<(clock() - deb)*1e-6 << endl;

    return 0;
}

long isqrt(long n)
{
   return (long)sqrt(n);
}

void fill_v()
{
    for (long i = 0; i <= L; i++) v[i] = i;
    for (long p = 2; p <= L; p++)
    {
        if (p == v[p])
        {
            long k = p;
            while (k <= L)
            {
                v[k] -= v[k]/p;
                k += p;
            }
        }
        v[p] = rem((v[p] + v[p-1]), modulo);
    }
}

long Phi(long n)
{
    if (n <= L) return v[n];
    if (cache.find(n) != cache.end()) return cache[n];
    long res;
    if (n % 2 == 0)
    {
        res = rem(rem(n / 2, modulo) * rem(n + 1,  modulo), modulo);
    }
    else
    {
        res = rem(rem(n, modulo) * rem((n + 1) / 2, modulo ), modulo);
    }
    long rac = isqrt(n);
    for (long g = 2; g <= rac; g++)
    {
        res = res - Phi(n/g);
    }
    for (long z = 1; z<= rac; z++)
    {
        if (n/z != z)
        {
            res = rem(res - rem(rem(n/z - n/(z+1), modulo) * rem(Phi(z), modulo), modulo), modulo);
        }
    }
    cache[n] = res;
    return res;
}

long rem ( long a, long b)
{
    long r = a % b;
    if ( a>=0 || r==0)
        return r;
    else return r+b;
}

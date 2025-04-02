#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <cfenv>
#include <ctime>
#include <set>

const double LIMIT = pow(10, 12);
const double SRL1 = sqrt(LIMIT) + 1;
char* p = 0;
const unsigned CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000;

void cleanup() { delete p; p = 0; }
bool is_prime(unsigned n) { return static_cast<bool>(p[n]); }
void init(unsigned l){p=new char[l];memset(p,1,l);p[0]=p[1]=0;for(unsigned i=2;i<l;++i){if(p[i]){for(unsigned j=i+i;j<l;j+=i){p[j]=0;}}}}
bool check(unsigned a, unsigned b, unsigned long long& sum, std::set<unsigned long long>& seen);

int main()
{
    std::clock_t start = std::clock();
    init(static_cast<unsigned>(SRL1));
    std::feclearexcept(FE_OVERFLOW);
    unsigned long long sum = 0;
    std::set<unsigned long long> seen;

    for (unsigned a = 2; a < SRL1; ++a)
    {
        for (unsigned b = a; b < SRL1; ++b)
        {
            if (!is_prime(a) || !is_prime(b))
            {
                if (!check(a, b, sum, seen) && !check(b, a, sum, seen)) break;
            }
        }
    }
    sum -= 16; // subtract 2^2^2 = 16 from the sum since 16 is not creative
    std::cout << "The sum of creative numbers less than " << LIMIT << " is " << sum << std::endl;
    cleanup();
    std::clock_t end = std::clock();
    std::cout << "Elapsed time " << static_cast<double>((end - start)) / CLOCKS_PER_MS << "ms" << std::endl;
}

bool check(unsigned a, unsigned b, unsigned long long& sum, std::set<unsigned long long>& seen)
{
    bool in_range = true;

    unsigned long long n = static_cast<unsigned long long>(pow(a, b));
    if (std::fetestexcept(FE_OVERFLOW) || n > LIMIT)
    {
        std::feclearexcept(FE_OVERFLOW);
        in_range = false;
    }
    else
    {
        if (seen.insert(n).second) sum += n;
    }

    return in_range;
}
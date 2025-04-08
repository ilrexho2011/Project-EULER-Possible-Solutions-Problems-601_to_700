#include <iostream>
#include <map>
#include <ctime>

using namespace std;

const int K = 60;
long long answer = 0;

map <int, int> m;

void rec(map<int, int>::iterator i, long long n = 1) {
    if (i == m.end()) {
        long long x = 1;
        int t = 0;
        do {
            (x *= 2) %= n;
            ++t;
        } while (x && x != 1 && t < K);
        if (x == 1 && t == K) {
            answer += n + 1;
        }
        return;
    }
    int prime = i->first;
    int number = i->second;
    ++i;
    for (int j = 0; j <= number; ++j) {
        rec(i, n);
        n *= prime;
    }
}

int main(int /* argc */, char** /* argv */)
{
    long long n = (1LL << K) - 1;
    for (long long i = 3; i * i <= n; i += 2) {
        while (n % i == 0) {
            m[i] += 1;
            n /= i;
        }
    }
    if (n > 1) {
        m[n] += 1;
    }
    rec(m.begin());

    cout << answer << endl;
    cerr << "Time execute: " << clock() / (double)CLOCKS_PER_SEC << " sec" << endl;
    return 0;
}
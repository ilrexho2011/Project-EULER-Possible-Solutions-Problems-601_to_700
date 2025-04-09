#include <iostream>
#include <vector>

using namespace std;

vector<long> cache(2048 * 2048, -1);

long modulo = 1000000007;

long lambdaStrict(long size, long numVars) {
    long key = numVars * 2048 + size;
    if (cache[key] >= 0) {
        return cache[key];
    }
    long result = 0;
    // Simple var
    if (size == 1) {
        result += numVars;
    } else {
        // Application
        if (size >= 4) {
            for (long i = 1; i <= (size - 2 - 1) / 2; ++i) {
                result += lambdaStrict(i, numVars) * lambdaStrict(size - 2 - i, numVars) * 2;
                result %= modulo;
            }
            if (size % 2 == 0) {
                result += lambdaStrict((size - 2) / 2, numVars) * lambdaStrict((size - 2) / 2, numVars) /* symmetric case */;
                result %= modulo;
            }
        }

        // New Lambda
        if (size >= 6) {
            result += lambdaStrict(size - 5, numVars + 1);
        }
        result %= modulo;
    }

    cache[key] = result;
    return result;
}

long lambdaStrict(long size) {
    long result = 0;
    // Initial lambda case
    result += lambdaStrict(size - 5, 1);
    // Initial application case
    for (long i = 6; i <= (size - 2 - 1) / 2; ++i) {
        result += lambdaStrict(i) * lambdaStrict(size - 2 - i) * 2;
        result %= modulo;
    }
    if (size % 2 == 0) {
        result += lambdaStrict((size - 2) / 2) * lambdaStrict((size - 2) / 2) /* symmetric case */;
        result %= modulo;
    }

    result %= modulo;
    return result;
}

long lambda(long size) {
    long result = 0;

    for (long i = 6; i <= size; ++i) {
        result += lambdaStrict(i, 0);
    }

    return result % modulo;
}

int main() {
    cout << "lambda(9): " << lambda(9) << endl;
    cout << "lambda(15): " << lambda(15) << endl;
    cout << "lambda(35): " << lambda(35) << endl;
    cout << "lambda(2000): " << lambda(2000) << endl;
}

#include <algorithm>
#include <cstdio>
#include <ctime>

using namespace std;

typedef long long int llint;

const int NUMBER_SIZE = 20000000;
const int PRIME_SIZE = 1000000;
int numbers[NUMBER_SIZE+1];
int primes[PRIME_SIZE];
int prime_size;

void init_primes() {
    int i, j, t;
    prime_size = 0;
    for (i=2; i<=NUMBER_SIZE; ++i) {
        if (numbers[i]==0) { // primes
            primes[prime_size++] = i;
            numbers[i] = i;
            if (prime_size==PRIME_SIZE) {
                break;
            }
        }

        t = NUMBER_SIZE / i;
        for (j=0; j<prime_size && primes[j]<=t; ++j) {
            numbers[i * primes[j]] = primes[j];

            if(numbers[i]==primes[j]) {
                break;
            }
        }
    }
}

struct NumberString
{
    llint length;       // total length
    llint prefix_sum;   // all prefix sum mod ANS_MOD
    llint suffix_sum;   // all suffix sum mod ANS_MOD
    llint ans_sum;      // the ans we want to cal
    llint val;          // the val of the string mod ANS_MOD
};


// const llint ANS_MOD = 10007;
const llint ANS_MOD = 1e9 + 7;
const llint CONCAT_NUM = 1e12;
llint inverse_9;


// a * b % ANS_MOD
llint mulModPrime(llint a, llint b) {
    if (a>=ANS_MOD) {
        a %= ANS_MOD;
    }
    if (b>=ANS_MOD) {
        b %= ANS_MOD;
    }

    return a * b % ANS_MOD;
}

// a^n % ANS_MOD
llint powModPrime(llint a, llint n) {
    if (a>=ANS_MOD) {
        a %= ANS_MOD;
    }
    if (n>=ANS_MOD-1) {
        n %= (ANS_MOD - 1);
    }

    llint ret = 1;
    while (n) {
        if (n&1) {
            ret = ret * a % ANS_MOD;
        }
        a = a * a % ANS_MOD;
        n >>= 1;
    }

    return ret;
}

// (10 + 10^1 + 10^2 + ... + 10^n) % ANS_MOD
llint getTenSumsModPrime(llint n) {

    // 10 * (10^n - 1) / (10-1)

    llint ans = powModPrime(10, n);
    ans = ans - 1;
    if (ans < 0) {
        ans += ANS_MOD;
    }

    ans = ans * 10 % ANS_MOD;
    ans = ans * inverse_9 % ANS_MOD;

    return ans;
}


// for debug
void output(const NumberString& ns) {
    printf("------------------\n");
    printf("length %lld\n",     ns.length);
    printf("prefix_sum %lld\n", ns.prefix_sum);
    printf("suffix_sum %lld\n", ns.suffix_sum);
    printf("val %lld\n",        ns.val);
    printf("ans_sum %lld\n",    ns.ans_sum);
}

NumberString initNumberString(int n) {
    int i, j;
    int data[10];
    int length = 0;
    while (n) {
        data[length++] = n % 10;
        n /= 10;
    }
    for (i=0, j=length-1; i<j; i++, j--) {
        swap(data[i], data[j]);
    }

    NumberString ns;

    ns.length = length;

    llint tmp, fac;

    ns.val = 0;
    ns.prefix_sum = 0;
    for (i=0; i<length; ++i) {
        ns.val = ns.val * 10 + data[i];
        if (ns.val >= ANS_MOD) {
            ns.val = ns.val % ANS_MOD;
        }

        ns.prefix_sum += ns.val;
        if (ns.prefix_sum >= ANS_MOD) {
            ns.prefix_sum -= ANS_MOD;
        }
    }

    ns.suffix_sum = 0;
    tmp = 0;
    fac = 1;
    for (i=length-1; i>=0; i--) {
        tmp = tmp + data[i] * fac;
        if (tmp >= ANS_MOD) {
            tmp %= ANS_MOD;
        }
        ns.suffix_sum += tmp;
        if (ns.suffix_sum >= ANS_MOD) {
            ns.suffix_sum -= ANS_MOD;
        }
        fac *= 10 % ANS_MOD;
    }

    ns.ans_sum = 0;
    for (i=0; i<length; ++i) {
        tmp = 0;
        for (j=i; j<length; ++j) {
            tmp = (tmp * 10 + data[j]) % ANS_MOD;
            ns.ans_sum += tmp;
            if (ns.ans_sum >= ANS_MOD) {
                ns.ans_sum -= ANS_MOD;
            }
        }
    }

    return ns;
}

// abc + def = abcdef
NumberString concatNumberString(const NumberString& left_number, const NumberString& right_number) {
    NumberString concatRet;
    concatRet.length = left_number.length + right_number.length;

    //
    concatRet.prefix_sum = left_number.prefix_sum + right_number.prefix_sum;
    concatRet.prefix_sum += mulModPrime(left_number.val, getTenSumsModPrime(right_number.length));
    concatRet.prefix_sum %= ANS_MOD;

    concatRet.suffix_sum = left_number.suffix_sum * powModPrime(10, right_number.length) % ANS_MOD;
    concatRet.suffix_sum += right_number.suffix_sum;
    concatRet.suffix_sum += mulModPrime(right_number.val, left_number.length);
    concatRet.suffix_sum %= ANS_MOD;

    concatRet.val = mulModPrime(left_number.val, powModPrime(10, right_number.length));
    concatRet.val = (concatRet.val + right_number.val) % ANS_MOD;

    concatRet.ans_sum = (left_number.ans_sum + right_number.ans_sum) % ANS_MOD;
    concatRet.ans_sum += mulModPrime(left_number.suffix_sum, getTenSumsModPrime(right_number.length));
    concatRet.ans_sum += mulModPrime(left_number.length, right_number.prefix_sum);
    concatRet.ans_sum %= ANS_MOD;

    return concatRet;
}


void init() {
    inverse_9 = powModPrime(9, ANS_MOD - 2);
}

// a + a + a = aaa
NumberString powConcat(NumberString a, llint n) {
    NumberString ret = a;
    n--;
    while (n) {
        if (n & 1) {
            ret = concatNumberString(ret, a);
        }
        a = concatNumberString(a, a);
        n >>= 1;
    }
    return ret;
}

int main() {

    clock_t start_time, end_time;
    start_time = clock();

    init_primes();
    end_time = clock();
    printf("primes process end, use time %.0f ms\n", (double)(end_time - start_time) / CLOCKS_PER_SEC * 1000);


    init();
    NumberString ns = initNumberString(primes[0]);
    for (int i=1; i<prime_size; ++i) {
        ns = concatNumberString(ns, initNumberString(primes[i]));
    }
    // output(ns);

    NumberString ans = powConcat(ns, CONCAT_NUM);
    // output(ans);

    clock_t end_time_2 = clock();
    printf("use time total %.0f ms\n", (double)(end_time_2 - end_time) / CLOCKS_PER_SEC * 1000);

    printf("process end, use time total %.0f ms\n", (double)(end_time_2 - start_time) / CLOCKS_PER_SEC * 1000);

    return 0;
}

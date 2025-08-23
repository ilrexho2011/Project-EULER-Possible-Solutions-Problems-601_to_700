#include <bits/stdc++.h>
using namespace std;
typedef long long LL;

LL Inverse(LL n, LL m) {
    n %= m;
    if (n <= 1) return n; // Handles properly (n = 0, m = 1).
    return m - ((m * Inverse(m, n) - 1) / n);
}

const LL mod = 1e9 + 7;
const LL inv2 = (mod+1)/2;

LL binom2(LL x) {
    LL res = x*(x-1) % mod;
    return res * inv2 % mod;
}
const int N = 2019;
LL path[N+1];
LL sympath[N+1];
LL node[N+1];
LL node_with_max[N+1][N+1];
LL subnode[N+1];
LL side[N+1];
LL len1[N+1];
LL len2[N+1];
LL len3[N+1];
LL len4[N+1];
LL len5[N+1];
LL tree[N+1];
LL choose_tree[N+1][N+1];
LL forest[N+1];
LL forest_with_max[N+1][N+1];

int main() {
    len1[1] = 1;
    len2[2] = 1;
    for (int n = 3; n <= N; n++) len3[n] = 1;
    for (int n = 4; n <= N; n++) len4[n] = (n-4)/2 + 1;
    
    
    node[0] = 1;
    node[1] = 1;
    for (int m = 0; m <= N; m++) node_with_max[1][m] = 1;
    for (int n = 2; n <= N; n++) {
        for (int m = 1; m <= n-1; m++) {
            node_with_max[n][m] = node_with_max[n-m][m];
        }
        for (int m = 1; m <= N; m++) {
            node_with_max[n][m] += node_with_max[n][m-1];
            node_with_max[n][m] %= mod;
        }
        node[n] = node_with_max[n][n-1] % mod;
    }

    for (int n = 3; n <= N; n++) {
        for (int k = 2; k <= n-1; k++) side[n] += node_with_max[n-k][k];
        side[n] %= mod;
    }

    for (int n = 5; n <= N; n++) {
        for (int k = 2; k <= n-1; k++) for (int h = k; h+k <= n-1; h++) len5[n] += node_with_max[n-k-h][k];
        len5[n] %= mod;
    }

    
    
    path[0] = 1;
    sympath[0] = 1;
    for (int n = 1; n <= N; n++) {
        for (int k = 1; k <= n; k++) path[n] += node[k]*path[n-k] % mod;
        path[n] %= mod;
    }
    for (int n = 1; n <= N; n++) {
        if (n%2 == 0) sympath[n] = path[n/2];
        for (int k = 1; k <= n; k++) {
            if ((n-k)%2 == 0) sympath[n] += node[k] * path[(n-k)/2] % mod;
        }
        sympath[n] %= mod;
    }

    tree[1] = 1;
    for (int n = 2; n <= N; n++) {
        tree[n] = len1[n] + len2[n] + len3[n] + len4[n] + len5[n];
        for (int h = 2; h <= n; h++) for (int k = h+1; h+k <= n; k++) {
            tree[n] += (side[h]*side[k] % mod)*path[n-h-k] % mod;
        }
        for (int h = 2; 2*h <= n; h++) {
            tree[n] += binom2(side[h])*path[n-2*h] % mod;
            tree[n] += (side[h] * (path[n-2*h]+sympath[n-2*h]) % mod) * inv2 %mod;
        }
        tree[n] %= mod;
    }

    
    for (int n = 1; n <= N; n++) {
        choose_tree[n][0] = 1;
        for (int k = 1; k <= N; k++) {
            LL coef = Inverse(k, mod) * (tree[n]+k-1) % mod;
            choose_tree[n][k] = choose_tree[n][k-1] * coef % mod;
        }
    }

    forest[0] = 1;
    for (int m = 0; m <= N; m++) forest_with_max[0][m] = 1;
    for (int n = 1 ; n <= N; n++) {
        for (int m = 1; m <= N; m++) {
            forest_with_max[n][m] = forest_with_max[n][m-1];
            for (int k = 1; k*m <= n; k++) {
                forest_with_max[n][m] += choose_tree[m][k]*forest_with_max[n-k*m][m-1] % mod;
            }
            forest_with_max[n][m] %= mod;
        }
        forest[n] = forest_with_max[n][n];
    }

    cout << forest[N] << endl;
}
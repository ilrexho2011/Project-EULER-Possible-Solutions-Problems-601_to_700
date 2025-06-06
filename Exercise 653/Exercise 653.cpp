#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e6 + 10;
int n, m, dir[MAXN];
ll L, r[MAXN], a[MAXN];

void solve(ll _L, int _n, int _m){
    n = _n, m = _m, L = 2 * _L;
    r[1] = 6563116;
    for (int i = 2; i <= n; i++)
        r[i] = (r[i - 1] * r[i - 1]) % 32745673;
    a[0] = 0;
    set<ll> mp1, mp2;
    for (int i = 1; i <= n; i++) {
        a[i] = a[i - 1] + (r[i] % 1000) * 2 + 2;
        dir[i] = r[i] <= 10000000;
        if (dir[i]) {
            mp1.insert(a[i]);
        }
        else {
            mp2.insert(a[i]);
            mp1.insert(-a[i]);
        }
    }
    ll ans = 0, t = 0, now = a[m];
    int d = dir[m];
    while (true) {
        if (d == 1) {
            ll u = now + t;
            auto aim = mp2.upper_bound(u);
            if (aim == mp2.end()) {
                ans += L - (now);
                break;
            }
            else {
                ll dt = (*aim - u) / 2;
                t += dt, ans += dt, now += dt;
            }
        }
        else {
            ll u = now - t;
            auto aim = mp1.lower_bound(u);
            if (aim == mp1.begin()) {
                ll dt = now;
                t += dt, ans += dt, now -= dt;
            }
            else {
                aim--;
                ll dt = (u - *aim) / 2;
                dt = min(dt, now);
                t += dt, ans += dt, now -= dt;
            }
        }
        d = 1 - d;
    }
    cout << ans / 2 - (m * 2 - 1) * 10 << endl;
}

int main(){
    solve(5000, 3, 2);
    solve(10000, 11, 6);
    solve(100000, 101, 51);
    solve(1000000000, 1000001, 500001);
    return 0;
}
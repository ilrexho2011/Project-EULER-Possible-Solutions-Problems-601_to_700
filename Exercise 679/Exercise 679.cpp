#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    int a[4];
    a[0] = stoi("2311", nullptr, 4);
    a[1] = stoi("2031", nullptr, 4);
    a[2] = stoi("0310", nullptr, 4);
    a[3] = stoi("3112", nullptr, 4);
    vector<int64_t> v1(1024, 0);
    for(int i = 0; i < 64; i++) {
        v1[i] = 1;
    }

    int n;
    cin >> n;

    for(int i = 4; i <= n; i++) {
        vector<int64_t> v2(1024, 0);
        for(int j = 0; j < 1024; j++) {
            int q = j & 63;
            int p = (j - q) >> 6;

            for(int k = 0; k < 4; k++) {
                bool flag = false;
                for(int h = 0; h < 4; h++) {
                    if(q * 4 + k == a[h]) {
                        flag = true;
                        if(p & (1 << h)) continue;
                        int t = ((p | (1<<h)) << 6) + ((q * 4 + k) & 63);
                        v2[t] += v1[j];
                        break;
                    }
                }
                if(!flag) {
                    int t = (p << 6) + ((q * 4 + k) & 63);
                    v2[t] += v1[j];
                }
            }
        }
        v1 = v2;
    }

    int64_t ans = 0;
    for(int i = 960; i < 1024; i++) {
        ans += v1[i];
    }
    cout << ans << endl;
    
    return 0;
}
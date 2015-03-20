#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 1000005;

int z[maxn];
int m, n;
char s[maxn];

inline int expand(int i, int j) {
    int cnt = 0;
    for(cnt = 0 ; j + cnt <= n ; ++ cnt)
        if(s[i + cnt] != s[j + cnt])
            return cnt;
    return cnt;
}

inline void buildz() {
    int l = -1, r = -1;
    memset(z, 0, sizeof(z));
    for(int i = 2 ; i <= n ; ++ i) {
        if(i > r) {
            z[i] = expand(1, i);
            if(z[i]) {
                l = i;
                r = i + z[i] - 1;
            }
        }
        else {
            int lasti = i - l + 1;
            if(z[lasti] < r - i + 1)
                z[i] = z[lasti];
            else {
                z[i] = r - i + 1 + expand(r - i + 2, r + 1);
                if(i + z[i] - 1 > r) {
                    r = i + z[i] - 1;
                    l = i;
                }
            }
        }
    }
    int maxim = 0;
    for(int i = 2 ; i <= n ; ++ i)
        if(i + z[i] - 1 == n) {
            maxim = max(maxim, z[i]);
            cout << (m - maxim) / (n - maxim) << '\n';
            return ;
        }
    cout << m / n << '\n';
    return ;
    cout << (m - maxim) / (n - maxim) << '\n';
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> m >> s + 1) {
        if(m == -1 || s[1] == '*')
            return 0;
        n = strlen(s + 1);

        if(n > m) {
            cout << "0\n";
            continue;
        }
        buildz();
    }

}

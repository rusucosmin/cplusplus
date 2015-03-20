#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxn = 20;

long long dp[1 << maxn];
int c, n;
bool a[maxn][maxn];

inline long long memo(int conf) {
    long long &ret = dp[conf];
    if(ret != -1)
        return ret;
    ret = 0;
    int cnt = __builtin_popcount(conf) - 1;
    for(int i = 0 ; i < n ; ++ i)
        if(a[cnt][i] && (conf & (1 << i)))
            ret += memo(conf ^ (1 << i));
    return ret;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    cin >> c;
    while(c -- ) {
        cin >> n;
        for(int i = 0 ; i < n ; ++ i)
            for(int j = 0 ; j < n ; ++ j)
                cin >> a[i][j];
        memset(dp, -1, sizeof(dp));
        dp[0] = 1;
        cout << memo((1 << n) - 1) << '\n';
        continue;
        for(int i = 1 ; i < (1 << n) ; ++ i) {
            int cnt = __builtin_popcount(i);
            -- cnt;
            //cerr << "conf " << i << " and " << cnt << ": ";
            for(int j = 0 ; j < n ; ++ j) {
                if(a[cnt][j])
                    dp[i] += dp[i ^ (1 << j)];
              //      cerr << j << ' ';
            }
            //cerr << '\n';
        }
        cout << dp[(1 << n) - 1] << '\n';
    }
}

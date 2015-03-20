#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 505;
const int oo = 0x3f3f3f3f;

int n, m, a[maxn][maxn], cnt[maxn], dp[maxn][maxn];

int main () {
    #ifndef ONLINE_JUDGE
    freopen("416e.in", "r", stdin);
    freopen("416e.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        a[x][y] = z;
        a[y][x] = z;
    }
    for(int i = 1 ; i <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j) {
            if(i == j)
                dp[i][j] = 0;
            else
                if(a[i][j])
                    dp[i][j] = a[i][j];
                else
                    dp[i][j] = oo;
            if(i == j)
                a[i][j] = 0;
            else
                if(!a[i][j])
                    a[i][j] = oo;
        }
    for(int k = 1 ; k <= n ; ++ k)
        for(int i = 1 ; i <= n ; ++ i)
            for(int j = 1 ; j <= n ; ++ j)
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);

    for(int s = 1 ; s <= n ; ++ s) {
        for(int i = 1 ; i <= n ; ++ i) {
            cnt[i] = 0;
            for(int j = 1 ; j <= n ; ++ j)
                if(i != j && dp[s][j] + a[j][i] == dp[s][i])
                    ++ cnt[i];
        }
        for(int t = s + 1 ; t <= n ; ++ t) {
            int ans = 0;
            if(dp[s][t] == oo) {
                cout << 0 << ' ';
                continue;
            }
            for(int i = 1 ; i <= n ; ++ i)
                if(dp[s][i] + dp[i][t] == dp[s][t])
                    ans += cnt[i];
            cout << ans << ' ';
        }
    }
}

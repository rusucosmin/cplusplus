#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 105;
const int maxp = 12;
const int oo = 0x3f3f3f3f;

int t, rf[maxn][maxn], n, m, b, dp[1 << maxp][maxn], p;
vector < pair<int, int> > v;

int main() {
    #ifndef ONLINE_JUDGE
    freopen("courier.in", "r", stdin);
    freopen("courier.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> t;
    while(t -- ) {
        v.clear();
        cin >> n >> m >> b;
        -- b;
        memset(rf, oo, sizeof(rf));
        for(int i = 0 ; i < m ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            -- x; -- y;
            rf[x][y] = min(rf[x][y], z);
            rf[y][x] = min(rf[y][x], z);
        }
        for(int i = 0 ; i < n ; ++ i)
            rf[i][i] = 0;
        for(int k = 0 ; k < n ; ++ k)
            for(int i = 0 ; i < n ; ++ i)
                for(int j = 0 ; j < n ; ++ j)
                    rf[i][j] = min(rf[i][j], rf[i][k] + rf[k][j]);
        cin >> p;
        for(int i = 0 ; i < p ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            -- x; -- y;
            for(int j = 0 ; j < z ; ++ j)
                v.push_back(make_pair(x, y));
        }
        memset(dp, oo, sizeof(dp));
        dp[0][0] = 0;
        p = v.size();
        for(int i = 0 ; i < p ; ++ i)
            dp[1 << i][v[i].second] = min(dp[1 << i][v[i].second],
            rf[b][v[i].first] + rf[v[i].first][v[i].second]);

        int maxmask = 1 << p;
        for(int mask = 0 ; mask < maxmask ; ++ mask)
            for(int i = 0 ; i < p ; ++ i)
                if(mask & (1 << i))
                    for(int j = 0 ; j < p ; ++ j)
                        if(mask & (1 << j)) {
                            int a = v[i].first;
                            int b = v[i].second;

                            int x = v[j].first;
                            int y = v[j].second;

                            /// am dus parcela j si vin sa iau parcela i
                            dp[mask][b] = min(dp[mask][b], dp[mask ^ (1 << i)][y] + rf[y][a] + rf[a][b]);
                        }
        int ans = 0x3f3f3f3f;
        for(int i = 0 ; i < n ; ++ i)
            ans = min(ans, dp[maxmask - 1][i] + rf[i][b]);
        cout << ans << '\n';
    }
}

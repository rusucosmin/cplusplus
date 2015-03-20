#include <iostream>
#include <fstream>

using namespace std;

const int maxn = 2005;
const int mod = 1000000007;

int n, k, dp[maxn][maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("415d.in", "r", stdin);
    freopen("415d.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> n >> k;
    for(int i = 1 ; i <= n ; ++ i)
        dp[1][i] = 1;
    for(int i = 1 ; i + 1 <= k ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            for(int k = 1 ; k * j <= n ; ++ k)
                dp[i + 1][k * j] = (dp[i + 1][k * j] + dp[i][j]) % mod;
    int ans = 0;
    for(int i = 1 ; i <= n ; ++ i)
        ans = (ans + dp[k][i]) % mod;
    cout << ans << '\n';
}

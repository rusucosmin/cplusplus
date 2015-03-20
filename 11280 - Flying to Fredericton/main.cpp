#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 105;
const int oo = 0x3f3f3f3f;

int dp[maxn][maxn], n, m, t;
unordered_map<string, int> _hash;
vector <pair<int, int> > g[maxn];

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> t;
    for(int test = 1 ; test <= t ; ++ test) {
        cin >> n;
        for(int i = 1 ; i <= n ; ++ i) {
            string s;
            cin >> s;
            _hash[s] = i;
        }
        cin >> m;
        for(int i = 1 ; i <= m ; ++ i) {
            string x, y;
            int z;
            cin >> x >> y >> z;
            g[_hash[y]].push_back(make_pair(_hash[x], z));
        }
        memset(dp, oo, sizeof(dp));
        dp[1][0] = 0;
        for(int i = 2 ; i <= n ; ++ i)
            for(int j = 0 ; j <= n ; ++ j)
                for(auto it : g[i])
                    dp[i][j] = min(dp[i][j], dp[it.first][j - 1] + it.second);
        cin >> m;
        cout << "Scenario #" << test << '\n';
        for(int i = 1 ; i <= m ; ++ i) {
            int x;
            cin >> x;
            int ans = oo;
            for(int i = 0 ; i <= x + 1; ++ i)
                ans = min(ans, dp[n][i]);
            if(ans != oo) {
                cout << "Total cost of flight(s) is $";
                cout << ans << '\n';
            }
            else
                cout << "No satisfactory flights\n";
        }
        if(test != t)
            cout << "\n";
        _hash.clear();
        for(int i = 1 ; i <= n ; ++ i)
            vector <pair<int, int> > ().swap(g[i]);
    }


}

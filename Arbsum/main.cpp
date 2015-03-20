#include <iostream>
#include <fstream>
#include <vector>
#include <string.h>

using namespace std;

const int maxn = 100005;

int n, dp[maxn][2], a[maxn];
vector <int> g[maxn];

inline void dfs(int node) {
    if(!g[node].size()) {
        dp[node][0] = 0;
        dp[node][1] = a[node];
        return ;
    }
    for(vector <int> :: iterator it = g[node].begin() ; it != g[node].end() ; ++ it) {
        dfs(*it);
        dp[node][0] = dp[node][0] + max(dp[*it][0], dp[*it][1]);
        dp[node][1] = dp[node][1] + dp[*it][0];
    }
    dp[node][1] = dp[node][1] + a[node];
}

int main() {
    freopen("arbsum.in", "r", stdin);
    ofstream fout("arbsum.out");

    scanf("%d", &n);
    for(int i = 1 ; i <= n ; ++ i) {
        int x;
        scanf("%d", &x);
        g[x].push_back(i);
    }
    for(int i = 1 ; i <= n ; ++ i)
        scanf("%d", &a[i]);
    dfs(1);
    fout << max(dp[1][0], dp[1][1]) << '\n';
}

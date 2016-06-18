#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>
#include <set>

using namespace std;

const int maxn = 15005;
const long long oo = (1LL << 60);

set <int> g[maxn];
int n, m;
int v[maxn];
long long dp[maxn], ans;
bitset <maxn> used;

void dfs(int node) {
    used[node] = 1;
    dp[node] = v[node];
    for(auto it : g[node]) {
        if(!used[it])
            dfs(it);
        dp[node] = max(dp[node], dp[it] + v[node]);
    }
    ans = max(ans, dp[node]);
}

int main() {
    ifstream fin("easygraph.in");
    ofstream fout("easygraph.out");

    int t;
    fin >> t;

    while(t --) {
        fin >> n >> m;
        for(int i = 1; i <= n; ++ i)
            fin >> v[i];
        while(m --) {
            int x, y;
            fin >> x >> y;
            g[x].insert(y);
        }
        used.reset();
        ans = -oo;
        for(int i = 1; i <= n; ++ i)
            if(!used[i])
                dfs(i);
        fout << ans << '\n';
        for(int i = 1; i <= n; ++ i)
            set <int> ().swap(g[i]);
    }
}

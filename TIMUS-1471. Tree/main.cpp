#include <iostream>
#include <vector>

using namespace std;

const int maxn = 50005;
const int maxlg = 22;

int n, anc[maxlg][maxn], level[maxn];
vector <pair<int, int> > g[maxn];
long long sum[maxn];

inline void dfs(int node, int father) {
    level[node] = level[father] + 1;
    anc[0][node] = father;
    for(auto it : g[node])
        if(it.first != father) {
            sum[it.first] = sum[node] + it.second;
            dfs(it.first, node);
        }
}

inline int lca(int x, int y) {
    if(level[x] < level[y])
        swap(x, y);
    int diff = level[x] - level[y];
    for(int i = 0 ; (1 << i) <= diff ; ++ i)
        if(diff & (1 << i))
            x = anc[i][x];
    if(x == y)
        return x;
    for(int i = maxlg - 1 ; i >= 0 ; -- i)
        if(anc[i][x] != anc[i][y]) {
            x = anc[i][x];
            y = anc[i][y];
        }
    return anc[0][x];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE

    cin >> n;
    for(int i = 1 ; i < n ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        ++ x; ++ y;
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    dfs(1, 0);
    for(int i = 1 ; (1 << i) <= n ; ++ i)
        for(int j = 1 ; j <= n ; ++ j)
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
    int m;
    cin >> m;
    while(m -- ) {
        int x, y;
        cin >> x >> y;
        ++ x; ++ y;
        cout << sum[x] + sum[y] - 2LL * sum[lca(x, y)] << '\n';
    }
}

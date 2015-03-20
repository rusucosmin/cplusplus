#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int maxn = 100005;
const int maxlg = 20;

int n, m, anc[maxlg][maxn], dpmin[maxlg][maxn], dpmax[maxlg][maxn], level[maxn];
vector <pair<int, int> > g[maxn];

inline void dfs(int node, int father) {
    level[node] = level[father] + 1;
    for(auto it : g[node]) {
        if(it.first == father)
            continue;
        anc[0][it.first] = node;
        dpmin[0][it.first] = it.second;
        dpmax[0][it.first] = it.second;
        dfs(it.first, node);
    }
}

inline void solve(int x, int y) {
    if(level[x] < level[y])
        swap(x, y);
    int diff = level[x] - level[y];
    int minedge = 0x3f3f3f3f, maxedge = -0x3f3f3f3f;
    for(int i = 0 ; (1 << i) <= diff ; ++ i)
        if(diff & (1 << i)) {
            minedge = min(minedge, dpmin[i][x]);
            maxedge = max(maxedge, dpmax[i][x]);
            x = anc[i][x];
        }
    if(x == y) {
        cout << minedge << ' ' << maxedge << '\n';
        return ;
    }
    for(int i = maxlg - 1 ; i >= 0 ; -- i)
        if(anc[i][x] != anc[i][y]) {
            minedge = min(minedge, min(dpmin[i][x], dpmin[i][y]));
            maxedge = max(maxedge, max(dpmax[i][x], dpmax[i][y]));
            x = anc[i][x];
            y = anc[i][y];
        }
    minedge = min(minedge, min(dpmin[0][x], dpmin[0][y]));
    maxedge = max(maxedge, max(dpmax[0][x], dpmax[0][y]));
    cout << minedge << ' ' << maxedge << '\n';
}

const int lim = (1 << 20);
int pos;
char buff[lim];

inline void getint(int &x) {
    x = 0;
    while(!('0' <= buff[pos] && buff[pos] <= '9'))
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    getint(n);
    for(int i = 1 ; i < n ; ++ i) {
        int x, y, z;
        getint(x);
        getint(y);
        getint(z);
        g[x].push_back(make_pair(y, z));
        g[y].push_back(make_pair(x, z));
    }
    dfs(1, 0);
    for(int i = 1 ; i < maxlg ; ++ i)
        for(int j = 1 ; j <= n ; ++ j) {
            anc[i][j] = anc[i - 1][anc[i - 1][j]];
            dpmin[i][j] = min(dpmin[i - 1][j], dpmin[i - 1][anc[i - 1][j]]);
            dpmax[i][j] = max(dpmax[i - 1][j], dpmax[i - 1][anc[i - 1][j]]);
        }
    getint(m);
    while(m -- ) {
        int x, y;
        getint(x);
        getint(y);
        solve(x, y);
    }
}

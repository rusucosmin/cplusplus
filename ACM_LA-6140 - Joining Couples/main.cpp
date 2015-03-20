#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <bitset>
#include <algorithm>
#include <string.h>

using namespace std;

const int maxlg = 20;
const int maxn = 100005;

int n, t, nxt[maxn], cycle[maxn], cyclepos[maxn], cyclecnt, cyclenodes, deg[maxn], anc[maxlg][maxn], cycle_sz[maxn], level[maxn];
vector <int> g[maxn];
bitset <maxn> incycle, used;

inline void dfs(int node) {
    for(auto it : g[node]) {
        if(incycle[it])
            continue;
        level[it] = level[node] + 1;
        cycle[it] = cycle[node];
        cyclepos[it] = cyclepos[node];
        anc[0][it] = node;
        for(int lg = 1 ; lg < maxlg ; ++ lg)
            anc[lg][it] = anc[lg - 1][anc[lg - 1][it]];
        dfs(it);
    }
}

inline int myabs(int x) {
    if(x >= 0)
        return x;
    return -x;
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

inline int solve(int x, int y) {
    if(cycle[x] != cycle[y])
        return -1;
    if(cyclepos[x] != cyclepos[y]) {
        int length = cycle_sz[cycle[x]];
        int d = myabs(cyclepos[x] - cyclepos[y]);
        return level[x] + level[y] + min(d, length - d);
    }
    return level[x] + level[y] - 2*level[lca(x, y)];
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    while(cin >> n) {
        level[0] = -1;
        for(int i = 1 ; i <= n ; ++ i) {
            cin >> nxt[i];
            g[nxt[i]].push_back(i);
            ++ deg[nxt[i]];
        }
        queue <int> q;
        for(int i = 1 ; i <= n ; ++ i) {
            if(deg[i] == 0)
                q.push(i);
            incycle[i] = 1;
        }
        while(!q.empty()) {
            int node = q.front();
            incycle[node] = 0;
            q.pop();
            if(-- deg[nxt[node]] == 0)
                q.push(nxt[node]);
        }
        for(int i = 1 ; i <= n ; ++ i)
            if(incycle[i]) {
                if(!used[i]) {
                    ++ cyclecnt;
                    int node = i;
                    do {
                        used[node] = 1;
                        cyclepos[node] = ++ cyclenodes;
                        cycle[node] = cyclecnt;
                        node = nxt[node];
                        ++ cycle_sz[cyclecnt];
                    }while(node != i);
                }
                dfs(i);
            }
        int m;
        cin >> m;
        while(m -- ) {
            int x, y;
            cin >> x >> y;
            cout << solve(x, y) << '\n';
        }
        for(int i = 1 ; i <= n ; ++ i)
            vector <int> ().swap(g[i]);
        memset(deg, 0, sizeof(deg));
        memset(anc, 0, sizeof(anc));
        memset(cycle, 0, sizeof(cycle));
        memset(cyclepos, 0, sizeof(cyclepos));
        memset(cycle_sz, 0, sizeof(cycle_sz));
        memset(level, 0, sizeof(level));
        used.reset();
        cyclecnt = 0;
        cyclenodes = 0;
    }
}

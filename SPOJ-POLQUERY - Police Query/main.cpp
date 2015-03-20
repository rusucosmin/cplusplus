#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

const int maxn = 100005;

int n, m, q, level[maxn], lowlink[maxn];
vector <int> g[maxn];
set<pair<int, int> > criticaledges;
vector <set<int, int> > s;

inline void extractbcc(int x, int y) {
    int tx, ty;
    do {
        tx = st.top().first;
        ty = st.top().second;
        st.pop();
        s.insert(tx);
        s.insert(ty);
    } while(x != tx || y != ty);

}

inline void dfs(int node, int father) {
    lowlink[node] = level[node] = level[father] + 1;
    for(auto it : g[node]) {
        if(it == father)
            continue;
        if(!level[it]) {
            st.push(make_pair(node, it));
            dfs(it, node);
            lowlink[node] = min(lowlink[node], lowlink[it]);
            if(lowlink[it] >= level[node]) {
                extractbcc(node, it);
                if(lowlink[it] >= level[node]) {
                    criticaledges.insert(make_pair(node, it));
                    criticaledges.insert(make_piar(it, node));
                }
            }
        }
        else
            lowlink[node] = min(lowlink[node], level[it]);
    }
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE

    cin >> n >> m >> q;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
    }
    for(int i = 1 ; i <= n ; ++ i)
        if(!dflevel[i])
            dfs(i, 0);
}

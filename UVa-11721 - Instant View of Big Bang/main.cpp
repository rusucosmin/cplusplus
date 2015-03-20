#include <iostream>
#include <fstream>
#include <string.h>
#include <stack>
#include <bitset>
#include <vector>
#include <queue>

using namespace std;

const int maxn = 1005;
const int oo = 0x3f3f3f3f;

int t, n, m, inds, ind[maxn], lowlink[maxn], ctc[maxn], comps, inqs[maxn], dist[maxn];
vector <pair<int, int> > g[maxn];
vector <int> comp[maxn], dagt[maxn];
bitset <maxn> inst, inq, cycle, reach;
stack <int> st;

inline void tarjan(int node) {
    ind[node] = lowlink[node] = ++ inds;
    st.push(node);
    inst[node] = 1;
    for(auto it : g[node]) {
        if(!ind[it.first]) {
            tarjan(it.first);
            lowlink[node] = min(lowlink[node], lowlink[it.first]);
        }
        else if(inst[it.first])
            lowlink[node] = min(lowlink[node], lowlink[it.first]);
    }
    if(lowlink[node] == ind[node]) {
        int x;
        ++ comps;
        do {
            x = st.top();
            st.pop();
            inst[x] = 0;
            ctc[x] = comps;
            comp[comps].push_back(x);
        } while(x != node);
    }
}

inline bool bellmanford(int stnode, int actcomp) {
    queue <int> q;
    memset(inqs, 0, sizeof(inqs));
    memset(dist, oo, sizeof(dist));
    dist[stnode] = 0;
    q.push(stnode);
    inq[stnode] = 1;
    inq.reset();
    while(!q.empty()) {
        int node = q.front();
        inq[node] = 0;
        q.pop();
        for(auto it : g[node]) {
            if(actcomp == ctc[it.first] && dist[it.first] > dist[node] + it.second) {
                dist[it.first] = dist[node] + it.second;
                if(inq[it.first])
                    continue;
                if(++ inqs[it.first] > comp[actcomp].size())
                    return 1;
                inq[it.first] = 1;
                q.push(it.first);
            }
        }
    }
    return 0;
}

inline void dfs(int node) {
    if(reach[node])
        return ;
    reach[node] = 1;
    for(auto it : dagt[node])
        dfs(it);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE

    cin >> t;
    int test = 0;
    while(t -- ) {
        cin >> n >> m;
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            ++ x; ++ y;
            g[x].push_back(make_pair(y, z));
        }
        for(int i = 1 ; i <= n ; ++ i)
            if(!ind[i])
                tarjan(i);
        for(int i = 1 ; i <= comps ; ++ i)
            if(bellmanford(comp[i][0], i))
                cycle[i] = 1;

        for(int i = 1 ; i <= n ; ++ i)
            for(auto it : g[i])
                if(ctc[i] != ctc[it.first])
                    dagt[ctc[it.first]].push_back(ctc[i]);

        for(int i = 1 ; i <= comps ; ++ i)
            if(cycle[i])
                dfs(i);

        cout << "Case " << ++ test << ":";
        bool okay = false;
        for(int i = 1 ; i <= n ; ++ i)
            if(reach[ctc[i]]) {
                cout << ' ' << i - 1;
                okay = true;
            }
        if(!okay)
            cout << " impossible\n";
        else
            cout << "\n";
        for(int i = 1 ; i <= n ; ++ i)
            vector <pair<int, int> > ().swap(g[i]);
        for(int i = 1 ; i <= comps ; ++ i) {
            vector <int> ().swap(comp[i]);
            vector <int> ().swap(dagt[i]);
        }
        memset(ind, 0, sizeof(ind));
        memset(lowlink, 0, sizeof(lowlink));
        memset(ctc, 0, sizeof(ctc));
        while(!st.empty())      st.pop();
        inst.reset();
        cycle.reset();
        reach.reset();
        inds = 0;
        comps = 0;
    }

}

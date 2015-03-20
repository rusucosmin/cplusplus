#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <bitset>
#include <cassert>

using namespace std;

const int maxn = 30;

unordered_map<string, int> ind;
unordered_map<int, string> rev;

int n, m, nodes;
vector <int> g[maxn], gt[maxn], discovered, ctc[maxn];
bitset <maxn> used;

inline void dfs(int node) {
    used[node] = 1;
    for(auto it : g[node])
        if(!used[it])
            dfs(it);
    discovered.push_back(node);
}

inline void dfst(int node, int comp) {
    used[node] = 0;
    ctc[comp].push_back(node);
    for(auto it : gt[node])
        if(used[it])
            dfst(it, comp);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif
    int test = 0;
    while(cin >> n >> m) {
        if(!n && !m)
            return 0;
        if(test != 0)
        cout << '\n';
        for(int i = 0 ; i < m ; ++ i) {
            string x, y;
            cin >> x >> y;
            if(!ind[x]) {
                ind[x] = ++ nodes;
                rev[nodes] = x;
            }
            if(!ind[y]) {
                ind[y] = ++ nodes;
                rev[nodes] = y;
            }
            g[ind[x]].push_back(ind[y]);
            gt[ind[y]].push_back(ind[x]);
        }
        assert(nodes == n);
        for(int i = 1 ; i <= n ; ++ i)
            if(!used[i])
                dfs(i);
        int actcomp = 0;
        for(auto it = discovered.rbegin() ; it != discovered.rend() ; ++ it)
            if(used[*it])
                dfst(*it, ++ actcomp);
        cout << "Calling circles for data set " << ++ test << ":\n";
        for(int i = 1 ; i <= actcomp ; ++ i) {
            cout << rev[ctc[i][0]];
            for(int j = 1 ; j < int(ctc[i].size()) ; ++ j)
                cout << ", " << rev[ctc[i][j]];
            cout << '\n';
        }
        discovered.clear();
        for(int i = 1 ; i <= nodes ; ++ i) {
            vector <int>().swap(g[i]);
            vector <int>().swap(gt[i]);
            vector <int>().swap(ctc[i]);
        }
        ind.clear();
        rev.clear();
        nodes = 0;
    }
}

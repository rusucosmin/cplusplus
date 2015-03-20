#include <iostream>
#include <vector>
#include <bitset>
#include <fstream>
#include <stack>

using namespace std;

ifstream fin("ctc.in");
ofstream fout("ctc.out");

const int maxn = 100005;

int n, m, ind[maxn], lowlink[maxn], indecs, comps;
vector <int> g[maxn], gt[maxn], tsort, ctc[maxn];
bitset <maxn> used, inst;
stack <int> st;

inline void dfs(int node) {
    used[node] = 1;
    for(auto it : g[node])
        if(!used[it])
            dfs(it);
    tsort.push_back(node);
}

inline void dfst(int node, int comp) {
    used[node] = 0;
    ctc[comp].push_back(node);
    for(auto it : gt[node])
        if(used[it])
            dfst(it, comp);
}

inline void kosaraju() {
    for(int i = 1 ; i <= n ; ++ i)
        if(!used[i])
            dfs(i);
    int comp = 0;
    for(auto it = tsort.rbegin(); it != tsort.rend() ; ++ it)
        if(used[*it])
            dfst(*it, ++ comp);
    fout << comp << '\n';
    for(int i = 1 ; i <= comp ; ++ i, fout << '\n')
        for(auto it : ctc[i])
            fout << it << ' ';
}

inline void tarjan(int node) {
    ind[node] = lowlink[node] = ++ indecs;
    st.push(node);
    inst[node] = 1;
    for(auto it : g[node]) {
        if(!ind[it]) {
            tarjan(it);
            lowlink[node] = min(lowlink[node], lowlink[it]);
        }
        else if(inst[it])
            lowlink[node] = min(lowlink[node], lowlink[it]);
    }
    if(ind[node] == lowlink[node]) {
        int x;
        ++ comps;
        do {
            x = st.top();
            st.pop();
            inst[x] = false;
            ctc[comps].push_back(x);
        }while (x != node);
    }
}

inline void tarjanalg() {
    for(int i = 1 ; i <= n ; ++ i)
        if(!ind[i])
            tarjan(i);
    fout << comps << '\n';
    for(int i = 1 ; i <= comps ; ++ i, fout << '\n')
        for(auto it : ctc[i])
            fout << it << ' ';
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
        gt[y].push_back(x);
    }
    ///kosaraju();
    tarjanalg();
}

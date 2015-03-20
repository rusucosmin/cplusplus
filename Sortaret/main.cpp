#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bitset>

using namespace std;
ifstream fin("sortaret.in");
ofstream fout("sortaret.out");

const int maxn = 50005;

int n, m;
vector <int> g[maxn], tsort;
bitset <maxn> used;

inline void dfs(int node) {
    used[node] = 1;
    for(auto it : g[node])
        if(!used[it])
            dfs(it);
    tsort.push_back(node);
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
    }
    for(int i = 1 ; i <= n ; ++ i)
        if(!used[i])
            dfs(i);
    for(auto it = tsort.rbegin() ; it != tsort.rend() ; ++ it)
        fout << *it << ' ';
}

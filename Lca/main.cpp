#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("lca.in");
ofstream fout("lca.out");

const int maxn = 100005;
const int maxlg = 25;

int n, m, first[maxn], euler[maxn << 1], rmq[maxlg][maxn << 1], lvl[maxn << 1], k, lg[maxn << 1];
vector <int> g[maxn];

inline void dfs(int node, int level) {
    first[node] = ++ k;
    euler[k] = node;
    lvl[k] = level;
    for(auto it : g[node]) {
        dfs(it, level + 1);
        euler[++ k] = node;
        lvl[k] = level;
    }
}

inline int lca(int x, int y) {
    x = first[x];
    y = first[y];
    if(x > y)
        swap(x, y);
    int l = lg[y - x + 1];
    int ret = rmq[l][x];
    if(lvl[ret] > lvl[rmq[l][y - (1 << l) + 1]])
        ret = rmq[l][y - (1 << l) + 1];
    return euler[ret];
}

int main() {
    fin >> n >> m;
    for(int i = 2 ; i <= n ; ++ i) {
        int x;
        fin >> x;
        g[x].push_back(i);
    }
    dfs(1, 1);
    for(int i = 2 ; i <= k ; ++ i)
        lg[i] = lg[i >> 1] + 1;
    for(int i = 1 ; i <= k ; ++ i)
        rmq[0][i] = i;
    for(int l = 1 ; (1 << l) <= k ; ++ l) {
        int aux = (1 << (l - 1));
        for(int j = 1 ; j + (1 << l) - 1 <= k ; ++ j) {
            rmq[l][j] = rmq[l - 1][j];
            if(lvl[rmq[l][j]] > lvl[rmq[l - 1][j + aux]])
                rmq[l][j] = rmq[l - 1][j + aux];
        }
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        fout << lca(x, y) << '\n';
    }
}

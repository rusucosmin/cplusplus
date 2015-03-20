#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

ifstream fin("dfs.in");
ofstream fout("dfs.out");

const int maxn = 100005;

int n, m, father[maxn];

inline int _find(int x) {
    if(father[x] != x)
        father[x] = _find(father[x]);
    return father[x];
}

inline bool unite(int x, int y) {
    x = _find(x);
    y = _find(y);
    if(x == y)
        return false;
    father[x] = y;
    return true;
}

int main() {
    fin >> n >> m;
    for(int i = 0 ; i < n ; ++ i)
        father[i] = i;
    for(int i = 1 ; i <= m ; ++ i) {
        int x, y;
        fin >> x >> y;
        -- x; -- y;
        if(unite(x, y))
            -- n;
    }
    fout << n << '\n';
}

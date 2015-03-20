#include <iostream>
#include <fstream>
#include <vector>
#include <bitset>

using namespace std;

ifstream fin("cuplaj.in");
ofstream fout("cuplaj.out");

const int maxn = 10005;

int n, m, l[maxn], r[maxn];
vector <int> g[maxn];
bitset <maxn> used;

inline bool pairup(int node) {
    if(used[node])
        return 0;
    used[node] = 1;
    for(auto it : g[node])
        if(!r[it]) {
            l[node] = it;
            r[it] = node;
            return 1;
        }
    for(auto it : g[node])
        if(pairup(r[it])) {
            l[node] = it;
            r[it] = node;
            return 1;
        }
    return 0;
}

int main() {
    int e;
    fin >> n >> m >> e;
    for(int i = 1 ; i <= e ; ++ i) {
        int x, y;
        fin >> x >> y;
        g[x].push_back(y);
    }
    int ans = 0;
    for(bool change = true ; change ; ) {
        change = false;
        used.reset();
        for(int i = 1 ; i <= n ; ++ i)
            if(!l[i] && pairup(i)) {
                change = true;
                ++ ans;
            }
    }
    fout << ans << '\n';
    for(int i = 1 ; i <= n ; ++ i)
        if(l[i])
            fout << i << ' ' << l[i] << '\n';
}

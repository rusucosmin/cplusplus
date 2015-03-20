#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

const int maxn = 100005;

int father[maxn], n, m, comp, pereche[maxn], col[maxn];

inline int _find(int x) {
    if(father[x] != x)
        father[x] = _find(father[x]);
    return father[x];
}

inline void unite(int x, int y) {
    father[x] = y;
}

int main(){
    ifstream fin("meciul.in");
    ofstream fout("meciul.out");

    int t;
    fin >> t;
    while(t -- ) {
        fin >> n >> m;
        for(int i = 1 ; i <= n ; ++ i)
            father[i] = i;
        memset(pereche, 0, sizeof(pereche));
        memset(col, 0, sizeof(col));
        comp = 0;
        for(int i = 1 ; i <= m ; ++ i) {
            int x, y;
            fin >> x >> y;
            if(!col[x] && !col[y]) {
                col[x] = ++ comp;
                col[y] = ++ comp;
                pereche[comp - 1] = comp;
                pereche[comp] = comp - 1;
                fout << "YES\n";
                continue;
            }
            if(col[x] && col[y]) {
                if(_find(col[x]) == _find(col[y])) {
                    fout << "NO\n";
                    continue;
                }
                int a = _find(col[x]);
                int b = _find(pereche[col[x]]);
                int c = _find(col[y]);
                int d = _find(pereche[col[y]]);
                unite(a, d);
                unite(b, c);
                continue;
            }
            if(col[x]) {
                col[y] = pereche[_find(col[x])];
                fout << "YES\n";
                continue;
            }
            if(col[y]) {
                col[x] = pereche[_find(col[y])];
                fout << "YES\n";
                continue;
            }
        }
    }

}

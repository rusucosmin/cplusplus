#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("disjoint.in");
ofstream fout("disjoint.out");

const int maxn = 100005;

int n, m, father[maxn];

inline int _find(int x) {
    if(father[x] != x)
        father[x] = _find(father[x]);
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i)
        father[i] = i;
    for(int i = 1 ; i <= m ; ++ i) {
        int op, x, y;
        fin >> op >> x >> y;
        int tx = _find(x);
        int ty = _find(y);
        if(op == 1)
            father[tx] = ty;
        else
            if(tx == ty)
                fout << "DA\n";
            else
                fout << "NU\n";
    }


}

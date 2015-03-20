#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int maxn = 100005;

ifstream fin("arbint.in");
ofstream fout("arbint.out");

int n, m, arb[maxn << 2];

inline void update(int node, int st, int dr, int x, int value) {
    if(st == dr) {
        arb[node] = value;
        return ;
    }
    int mid = ((st + dr) >> 1);
    if(x <= mid)
        update(node << 1, st, mid, x, value);
    else
        update((node << 1) | 1, mid + 1, dr, x, value);
    arb[node] = max(arb[node << 1], arb[(node << 1) | 1]);
}

inline int query(int node, int st, int dr, int a, int b) {
    if(a <= st && dr <= b)
        return arb[node];
    int mid = ((st + dr) >> 1);
    int ret = -0x3f3f3f3f;
    if(a <= mid)
        ret = query(node << 1, st, mid, a, b);
    if(mid < b)
        ret = max(ret, query((node << 1) | 1, mid + 1, dr, a, b));
    return ret;
}

int main() {
    fin >> n >> m;
    for(int i = 1 ; i <= n ; ++ i) {
        int x;
        fin >> x;
        update(1, 1, n, i, x);
    }
    for(int i = 1 ; i <= m ; ++ i) {
        int op, x, y;
        fin >> op >> x >> y;
        if(op == 0)
            fout << query(1, 1, n, x, y) << '\n';
        else
            update(1, 1, n, x, y);
    }
}

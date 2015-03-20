#include <fstream>
#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <iomanip>
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <deque>

using namespace std;

const char infile[] = "input.in";
const char outfile[] = "output.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, X[MAXN], pathWhere[MAXN], pathFather[MAXN], level[MAXN], heavy[MAXN], M;
int st[MAXN], numPaths;
long long Y[MAXN];
Graph G;

inline long long crossProduct(int a, int b, int c) {
    /// (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x)
    return 1LL * (X[b] - X[a]) * (Y[c] - Y[a]) - 1LL * (Y[b] - Y[a]) * (X[c] - X[a]);
}

inline void DFs(int Node, int father, int actLevel) {
    level[Node] = actLevel;
    heavy[Node] = 1;
    int heaviest = -1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == father)
            continue;
        DFs(*it, Node, actLevel + 1);
        heavy[Node] += heavy[*it];
        if(heaviest == -1 || heavy[heaviest] < heavy[*it])
            heaviest = *it;
    }
    if(heaviest == -1) {
        pathWhere[Node] = ++ numPaths;
        pathFather[pathWhere[Node]] = father;
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    pathFather[pathWhere[Node]] = father;
}

inline int LCA(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        if(level[x] > level[y])
            swap(x, y);
        return x;
    }
    if(level[pathFather[pathWhere[x]]] < level[pathFather[pathWhere[y]]])
        swap(x, y);
    return LCA(pathFather[pathWhere[x]], y);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N;
    for(int i = 1 ; i <= N ; ++ i)
        cin >> X[i] >> Y[i];
    st[++ st[0]] = N;
    for(int i = N - 1 ; i > 0 ; -- i) {
        while(st[0] > 1 && crossProduct(st[st[0] - 1], st[st[0]], i) < 0)
            -- st[0];
        G[st[st[0]]].push_back(i);
        st[++ st[0]] = i;
    }
    DFs(N, 0, 1);
    cin >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        cout << LCA(x, y) << ' ';
    }
    return 0;
}

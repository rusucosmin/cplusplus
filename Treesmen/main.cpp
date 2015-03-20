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

const char infile[] = "treesmen.in";
const char outfile[] = "treesmen.out";

ofstream fout(outfile);

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

const int lim = 1 << 20;
char buff[lim];
int pos;

inline void getInt(int &x) {
    while(!('0' <= buff[pos] && buff[pos] <= '9')) {
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
    x = 0;
    while('0' <= buff[pos] && buff[pos] <= '9') {
        x = x * 10 + buff[pos] - '0';
        if(++ pos == lim) {
            pos = 0;
            fread(buff, 1, lim, stdin);
        }
    }
}

struct Node {
    long long a;
    long long r;
    long long sum;
    bool lazy;
    Node() {
        a = r = 0LL;
        sum = 0LL;
        lazy = false;
    }
};

int paths, depth[MAXN], subtree[MAXN];
Graph G;
vector <int> Path[MAXN];
vector <Node> arb[MAXN];
int pathWhere[MAXN], pathPosition[MAXN], pathFather[MAXN];

inline void lazyUpdate(int Node, int st, int dr, int x, int y, long long a, long long r, int index) {
    arb[index][Node].lazy = true;
    arb[index][Node].a += a;
    arb[index][Node].r += r;
    arb[index][Node].sum += ( 1LL * (dr - st + 1) * a + 1LL * (dr - st + 1) * (dr - st) / 2 * r );
}

inline void Update(int Node, int st, int dr, int x, int y, long long a, long long r, int index) {
    if(x <= st && dr <= y) {
        arb[index][Node].lazy = true;
        arb[index][Node].a += (a + 1LL * (st - x) * r);
        arb[index][Node].r += r;
        arb[index][Node].sum += ( 1LL * (dr - st + 1) * (a + (st - x) * r) + 1LL * (dr - st + 1) * (dr - st) / 2 * r );
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[index][Node].lazy) {
        lazyUpdate(Node << 1, st, mid, st, mid, arb[index][Node].a, arb[index][Node].r, index);
        lazyUpdate((Node << 1) | 1, mid + 1, dr, mid + 1, dr, arb[index][Node].a + 1LL * (mid + 1 - st) * arb[index][Node].r, arb[index][Node].r, index);
        arb[index][Node].lazy = 0;
        arb[index][Node].a = 0;
        arb[index][Node].r = 0;
    }
    if(x <= mid)
        Update(Node << 1, st, mid, x, y, a, r, index);
    if(mid < y)
        Update((Node << 1) | 1, mid + 1, dr, x, y, a, r, index);
    arb[index][Node].sum = arb[index][Node << 1].sum + arb[index][(Node << 1) | 1].sum;
}

inline long long Query(int Node, int st, int dr, long long a, long long b, int index) {
    if(a <= st && dr <= b)
        return arb[index][Node].sum;
    int mid = ((st + dr) >> 1);
    if(arb[index][Node].lazy) {
        lazyUpdate(Node << 1, st, mid, st, mid, arb[index][Node].a, arb[index][Node].r, index);
        lazyUpdate((Node << 1) | 1, mid + 1, dr, mid + 1, dr, arb[index][Node].a + 1LL * (mid + 1 - st) * arb[index][Node].r, arb[index][Node].r, index);
        arb[index][Node].lazy = 0;
        arb[index][Node].a = 0;
        arb[index][Node].r = 0;
    }
    long long sum = 0;
    if(a <= mid)
        sum += Query(Node << 1, st, mid, a, b, index);
    if(mid < b)
        sum += Query((Node << 1) | 1, mid + 1, dr, a, b, index);
    return sum;
}

inline void dfs(int node, int level, int father) {
    depth[node] = level;
    subtree[node] = 1;
    int deepest = -1;
    for(It it = G[node].begin(), fin = G[node].end(); it != fin ; ++ it) {
        dfs(*it, level + 1, node);
        subtree[node] += subtree[*it];
        if(deepest == -1 || subtree[deepest] < subtree[*it])
            deepest = *it;
    }
    if(deepest == -1) {
        pathWhere[node] = ++ paths;
        Path[pathWhere[node]].push_back(node);
        pathFather[pathWhere[node]] = father;
        return;
    }
    pathWhere[node] = pathWhere[deepest];
    Path[pathWhere[node]].push_back(node);
    pathFather[pathWhere[node]] = father;
}

inline void prepareHeavyPath() {
    for(int i = 1 ; i <= paths ; ++ i) {
        reverse(Path[i].begin(), Path[i].end());
        for(int j = 0 ; j < Path[i].size() ; ++ j)
            pathPosition[Path[i][j]] = j;
        arb[i].resize(4 * Path[i].size());
    }
}

inline void UpdateHeavyPath(int x, int y, long long a, long long r) {
    if(pathWhere[x] == pathWhere[y]) {
        Update(1, 0, Path[pathWhere[y]].size() - 1, pathPosition[x], pathPosition[y], a, r, pathWhere[y]);
        return;
    }
    Update(1, 0, Path[pathWhere[y]].size() - 1, 0, pathPosition[y],  a + r * (depth[Path[pathWhere[y]][0]] - depth[x]), r, pathWhere[y]);
    UpdateHeavyPath(x, pathFather[pathWhere[y]], a, r);
}

int main() {
    freopen(infile, "r", stdin);
    int N, M;
    getInt(N);
    for(int i = 2 ; i <= N ; ++ i) {
        int x;
        getInt(x);
        G[x].push_back(i);
    }
    dfs(1, 1, 0);
    prepareHeavyPath();
    getInt(M);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y, p, r;
        getInt(op);
        if(op == 0) {
                getInt(x); getInt(y); getInt(p); getInt(r);
                UpdateHeavyPath(x, y, 1LL * p, 1LL * r);
        } else {
            getInt(x);
            fout << Query(1, 0, Path[pathWhere[x]].size() - 1, pathPosition[x], pathPosition[x], pathWhere[x]) << '\n';
        }
    }
    fout.close();
    return 0;
}

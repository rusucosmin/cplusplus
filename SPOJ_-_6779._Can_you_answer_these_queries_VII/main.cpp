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
const int oo = (1 << 25);

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct node {
    int sum, pref, suf, best;
    bool lazy;
    int add;
    node(){
        Update(0);
    }
    void Update(int value) {
        sum = value;
        pref = suf = value;
        best = max(0, value);
    }
    void Update(node Left, node Right) {
        sum = Left.sum + Right.sum;
        pref = max(Left.pref, Left.sum + Right.pref);
        suf = max(Right.suf, Right.sum + Left.suf);
        best = max(Left.best, Right.best);
        best = max(best, Left.suf + Right.pref);
    }
};

int N, Q, numPaths, a[MAXN], heavy[MAXN], depth[MAXN], pathWhere[MAXN], pathPosition[MAXN];
int pathFather[MAXN];
vector <int> path[MAXN];
vector <node> arb[MAXN];
Graph G;

void DFs(int Node, int Father, int actLevel) {
    heavy[Node] = 1;
    depth[Node] = actLevel;
    int heaviest = -1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node, actLevel + 1);
        heavy[Node] += heavy[*it];
        if(heaviest == -1)
            heaviest = *it;
        else if(heavy[heaviest] < heavy[*it])
            heaviest = *it;
    }
    if(heaviest == -1) {
        pathWhere[Node] = ++ numPaths;
        pathFather[pathWhere[Node]] = Father;
        path[pathWhere[Node]].push_back(Node);
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    pathFather[pathWhere[Node]] = Father;
    path[pathWhere[Node]].push_back(Node);
}

void Build(int Node, int st, int dr, int whichPath) {
    if(st == dr) {
        arb[whichPath][Node].Update(a[path[whichPath][st]]);
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid, whichPath);
    Build(2*Node + 1, mid + 1, dr, whichPath);
    arb[whichPath][Node].Update(arb[whichPath][2*Node], arb[whichPath][2*Node + 1]);
}

void Update(int Node, int st, int dr, int a, int b, int whichPath, int value) {
    if(a <= st && dr <= b) {
        arb[whichPath][Node].Update((dr - st + 1) * value);
        arb[whichPath][Node].lazy = 1;
        arb[whichPath][Node].add = value;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[whichPath][Node].lazy == 1) {
        Update(2*Node, st, mid, st, mid, whichPath, arb[whichPath][Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, whichPath, arb[whichPath][Node].add);
        arb[whichPath][Node].lazy = 0;
        arb[whichPath][Node].add = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, whichPath, value);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, whichPath, value);
    arb[whichPath][Node].Update(arb[whichPath][2*Node], arb[whichPath][2*Node + 1]);
}

node Query(int Node, int st, int dr, int a, int b, int whichPath) {
    if(a <= st && dr <= b)
        return arb[whichPath][Node];
    int mid = ((st + dr) >> 1);
    if(arb[whichPath][Node].lazy == 1) {
        Update(2*Node, st, mid, st, mid, whichPath, arb[whichPath][Node].add);
        Update(2*Node+1, mid+1, dr, mid+1, dr, whichPath, arb[whichPath][Node].add);
        arb[whichPath][Node].lazy = 0;
        arb[whichPath][Node].add = 0;
    }
    node Left, Right;
    if(a <= mid)
        Left = Query(2*Node, st, mid, a, b, whichPath);
    if(mid < b)
        Right = Query(2*Node + 1, mid + 1, dr, a, b, whichPath);
    node Father;
    Father.Update(Left, Right);
    return Father;
}

void UpdateHeavyPath(int x, int y, int c) {
    if(pathWhere[x] == pathWhere[y]) {
        if(pathPosition[x] > pathPosition[y])
            swap(x, y);
        Update(1, 0, path[pathWhere[x]].size() - 1, pathPosition[x], pathPosition[y], pathWhere[x], c);
        return;
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    Update(1, 0, path[pathWhere[x]].size() - 1, 0, pathPosition[x], pathWhere[x], c);
    UpdateHeavyPath(pathFather[pathWhere[x]], y, c);
}

int LCA(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        if(depth[x] > depth[y])
            swap(x, y);
        return x;
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    return LCA(pathFather[pathWhere[x]], y);
}

node QueryHeavyPath(int x, int y, int lca) {
    node _First, _Second, Father;
    node aux;
    node act;
    while(pathWhere[x] != pathWhere[lca]) {
        act = Query(1, 0, path[pathWhere[x]].size() - 1, 0, pathPosition[x], pathWhere[x]);
        aux.Update(act, _First);
        _First = aux;
        x = pathFather[pathWhere[x]];
    }

    act = Query(1, 0, path[pathWhere[x]].size() - 1, pathPosition[lca], pathPosition[x], pathWhere[x]);
    aux.Update(act, _First);
    _First = aux;
    while(pathWhere[y] != pathWhere[lca]) {
        act = Query(1, 0, path[pathWhere[y]].size() - 1, 0, pathPosition[y], pathWhere[y]);
        aux.Update(act, _Second);
        _Second = aux;
        y = pathFather[pathWhere[y]];
    }
    if(pathPosition[lca] != pathPosition[y]) {
        act = Query(1, 0, path[pathWhere[y]].size() - 1, pathPosition[lca] + 1, pathPosition[y], pathWhere[y]);
        aux.Update(act, _Second);
        _Second = aux;
    }
    Father.best = max(_First.best, _Second.best);
    Father.best = max(Father.best, _First.pref + _Second.pref);
    return Father;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i)
        scanf("%d", &a[i]);
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    for(int i = 1 ; i <= numPaths ; ++ i) {
        reverse(path[i].begin(), path[i].end());
        for(int j = 0 ; j < int(path[i].size()) ; ++ j)
            pathPosition[path[i][j]] = j;
        arb[i].resize(4 * path[i].size());
        Build(1, 0, path[i].size() - 1, i);
    }
    scanf("%d", &Q);
    for(int i = 1 ; i <= Q ; ++ i) {
        int op, x, y, c;
        scanf("%d %d %d", &op, &x, &y);
        switch(op) {
        case 1:
            printf("%d\n", max(0, QueryHeavyPath(x, y, LCA(x, y)).best));
            break;
        case 2:
            scanf("%d", &c);
            UpdateHeavyPath(x, y, c);
            break;
        }
    }
    return 0;
}

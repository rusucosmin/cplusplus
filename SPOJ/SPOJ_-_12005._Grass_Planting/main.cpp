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

const int MAXN = 100005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

struct nod {
    int sum, add;
    bool vis;
};

int N, M, numPaths;
int heavy[MAXN], pathFather[MAXN], pathWhere[MAXN], depth[MAXN], pathPosition[MAXN];
vector <int> Path[MAXN];
vector <nod> arb[MAXN];
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
        else if(heavy[*it] > heavy[heaviest])
            heaviest = *it;
    }
    if(heaviest == -1) {
        pathWhere[Node] = ++ numPaths;
        pathFather[pathWhere[Node]] = Father;
        Path[pathWhere[Node]].push_back(Node);
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    pathFather[pathWhere[Node]] = Father;
    Path[pathWhere[Node]].push_back(Node);
}

void Update(int Node, int st, int dr, int a, int b, int whichPath, int value) {
    if(a <= st && dr <= b) {
        arb[whichPath][Node].sum += value * (dr - st + 1);
        arb[whichPath][Node].add += value;
        arb[whichPath][Node].vis = 1;
        return;
    }
    int mid = ((st + dr) >> 1);
    if(arb[whichPath][Node].vis == 1) {
        Update(2*Node, st, mid, st, mid, whichPath, arb[whichPath][Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, whichPath, arb[whichPath][Node].add);
        arb[whichPath][Node].add = 0;
        arb[whichPath][Node].vis = 0;
    }
    if(a <= mid)
        Update(2*Node, st, mid, a, b, whichPath, value);
    if(mid < b)
        Update(2*Node + 1, mid + 1, dr, a, b, whichPath, value);
    arb[whichPath][Node].sum = arb[whichPath][2*Node].sum + arb[whichPath][2*Node + 1].sum;
}

int Query(int Node, int st, int dr, int a, int b, int whichPath) {
    if(a <= st && dr <= b)
        return arb[whichPath][Node].sum;
    int mid = ((st + dr) >> 1);
    if(arb[whichPath][Node].vis == 1) {
        Update(2*Node, st, mid, st, mid, whichPath, arb[whichPath][Node].add);
        Update(2*Node + 1, mid + 1, dr, mid + 1, dr, whichPath, arb[whichPath][Node].add);
        arb[whichPath][Node].add = 0;
        arb[whichPath][Node].vis = 0;
    }
    int ret = 0;
    if(a <= mid)
        ret += Query(2*Node, st, mid, a, b, whichPath);
    if(mid < b)
        ret += Query(2*Node + 1, mid + 1, dr, a, b, whichPath);
    return ret;
}

void UpdateHeavyPath(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        if(pathPosition[x] > pathPosition[y])
            swap(x, y);
        if(pathPosition[x] == pathPosition[y])
            return;
        Update(1, 0, Path[pathWhere[x]].size() - 1, pathPosition[x] + 1, pathPosition[y], pathWhere[x], 1);
        return;
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    Update(1, 0, Path[pathWhere[x]].size() - 1, 0, pathPosition[x], pathWhere[x], 1);
    UpdateHeavyPath(pathFather[pathWhere[x]], y);
}

int QueryHeavyPath(int x, int y) {
    //cout << "QueryHeavyPath " << x << ' ' << y << "\n\n";
    if(pathWhere[x] == pathWhere[y]) {
        if(pathPosition[x] > pathPosition[y])
            swap(x, y);
        if(pathPosition[x] == pathPosition[y])
            return 0;
        return Query(1, 0, Path[pathWhere[x]].size() - 1, pathPosition[x] + 1, pathPosition[y], pathWhere[x]);
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    int ret = Query(1, 0, Path[pathWhere[x]].size() - 1, 0, pathPosition[x], pathWhere[x]);
    return ret + QueryHeavyPath(pathFather[pathWhere[x]], y);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    cin >> N >> M;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        cin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    for(int i = 1 ; i <= numPaths ; ++ i) {
        reverse(Path[i].begin(), Path[i].end());
        for(int j = 0 ; j < int(Path[i].size()) ; ++ j)
            pathPosition[Path[i][j]] = j;
        arb[i].resize(4*Path[i].size());
    }
    for(int i = 1 ; i <= M ; ++ i) {
        char c;
        int x, y;
        cin >> c >> x >> y;
        switch(c) {
        case 'P':
            UpdateHeavyPath(x, y);
            break;
        case 'Q':
            cout << QueryHeavyPath(x, y) << '\n';
            break;
        }
    }
    return 0;
}

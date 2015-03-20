#include <iostream>
#include <vector>
#include <bitset>
#include <string.h>
#include <algorithm>
#include <string>
#include <stdio.h>

using namespace std;

const int MAXN = 10005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, T, numPaths;
int depth[MAXN];
int pathWhere[MAXN];
int pathPosition[MAXN];
int pathFather[MAXN];
int heavy[MAXN];
int v[MAXN];
int edgeIdx[MAXN];
pair<int, int> edge[MAXN];
vector <int> path[MAXN];
vector <int> arb[MAXN];
Graph G;

void Build(int Node, int st, int dr, int whichPath) {
    if(st == dr) {
        arb[whichPath][Node] = v[edgeIdx[path[whichPath][st]]];
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(2*Node, st, mid, whichPath);
    Build(2*Node+1, mid + 1, dr, whichPath);
    arb[whichPath][Node] = max(arb[whichPath][2*Node], arb[whichPath][2*Node + 1]);
}

void Update(int Node, int st, int dr, int pos, int whichPath) {
    if(st == dr) {
        arb[whichPath][Node] = v[edgeIdx[path[whichPath][pos]]];
        return;
    }
    int mid = ((st + dr) >> 1);
    if(pos <= mid)
        Update(2*Node, st, mid, pos, whichPath);
    else Update(2*Node + 1, mid + 1, dr, pos, whichPath);
    arb[whichPath][Node] = max(arb[whichPath][2*Node], arb[whichPath][2*Node + 1]);
}

int Query(int Node, int st, int dr, int a, int b, int whichPath) {
    if(a <= st && dr <= b)
        return arb[whichPath][Node];
    int mid = ((st + dr) >> 1);
    int retMax = -oo;
    if(a <= mid)
        retMax = max(retMax, Query(2*Node, st, mid, a, b, whichPath));
    if(mid < b)
        retMax = max(retMax, Query(2*Node + 1, mid + 1, dr, a, b, whichPath));
    return retMax;
}

void DFs(int Node, int Father, int actLevel, int edge) {
    depth[Node] = actLevel;
    heavy[Node] = 1;
    int heaviest = -1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(it->first == Father)
            continue;
        DFs(it->first, Node, actLevel + 1, it->second);
        heavy[Node] += heavy[it->first];
        if(heaviest == -1)
            heaviest = it->first;
        else if(heavy[heaviest] < heavy[it->first])
            heaviest = it->first;
    }
    edgeIdx[Node] = edge;
    if(heaviest == -1) {
        pathWhere[Node] = ++ numPaths;
        path[numPaths].clear();
        path[pathWhere[Node]].push_back(Node);
        pathFather[numPaths] = Father;
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    path[pathWhere[Node]].push_back(Node);
    pathFather[pathWhere[Node]] = Father;
}

int QueryHeavyPath(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        if(pathPosition[x] > pathPosition[y])
            swap(x, y);
        if(pathPosition[x] == pathPosition[y])
            return 0;
        return Query(1, 0, path[pathWhere[x]].size() - 1, pathPosition[x] + 1, pathPosition[y], pathWhere[x]);
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    int retMax = Query(1, 0, path[pathWhere[x]].size() - 1, 0, pathPosition[x], pathWhere[x]);
    return max(retMax, QueryHeavyPath(pathFather[pathWhere[x]], y));
}

int main() {
    /*#ifndef ONLINE_JUDGE
    freopen("input.in", "r", stdin);
    freopen("output.out", "w", stdout);
    #endif // ONLINE_JUDGE
    */scanf("%d", &T);
    for(int test = 1 ; test <= T ; ++ test) {
        scanf("%d", &N);
        for(int i = 1 ; i != N ; ++ i) {
            int x, y;
            scanf("%d %d %d", &x, &y, &v[i]);
            edge[i] = make_pair(x, y);
            G[x].push_back(make_pair(y, i));
            G[y].push_back(make_pair(x, i));
        }
        v[0] = -oo;
        DFs(1, 0, 1, 0);
        for(int i = 1 ; i <= numPaths ; ++ i) {
            reverse(path[i].begin(), path[i].end());
            for(int j = 0 ; j < int(path[i].size()) ; ++ j)
                pathPosition[path[i][j]] = j;
            arb[i].resize(4*path[i].size());
            Build(1, 0, path[i].size() - 1, i);
        }
        char op[10];
        int x, y;
        while(scanf("%s", &op)) {
            if(op[0] == 'D')
                break;
            scanf("%d %d", &x, &y);
            if(op[0] == 'C') {
                v[x] = y;
                if(depth[edge[x].first] > depth[edge[x].second])
                    x = edge[x].first;
                else x = edge[x].second;
                Update(1, 0, path[pathWhere[x]].size() - 1, pathPosition[x], pathWhere[x]);
            }
            else if(op[0] == 'Q')
                cout << QueryHeavyPath(x, y) << '\n';
            else break;
        }
        for(int i = 1 ; i <= N ; ++ i)
            G[i].clear();
        numPaths = 0;
    }
    return 0;
}

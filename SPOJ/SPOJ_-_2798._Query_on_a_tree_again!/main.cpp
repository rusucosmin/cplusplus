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

int N, M, heavy[MAXN], numPaths, depth[MAXN];
int pathFather[MAXN], pathWhere[MAXN];
set <pair<int, int> > heavyPath[MAXN];
bitset <MAXN> black;
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
        ++ numPaths;
        pathWhere[Node] = numPaths;
        pathFather[pathWhere[Node]] = Father;
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    pathFather[pathWhere[Node]] = Father;
}

void UpdateHeavyPath(int Node) {
    black[Node] = !black[Node];
    if(black[Node])
        heavyPath[pathWhere[Node]].insert(make_pair(depth[Node], Node));
    else heavyPath[pathWhere[Node]].erase(make_pair(depth[Node], Node));
}

int QueryHeavyPath(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        set <pair<int, int> > :: iterator it = heavyPath[pathWhere[x]].lower_bound(make_pair(depth[x], x));
        if(it == heavyPath[pathWhere[x]].end() || it->first > depth[y])
            return -1;
        return it->second;
    }
    int actHighest = QueryHeavyPath(x, pathFather[pathWhere[y]]);
    if(actHighest != -1)
        return actHighest;
    set <pair<int, int> > :: iterator it = heavyPath[pathWhere[y]].begin();
    if(it == heavyPath[pathWhere[y]].end() || it->first > depth[y])
        return -1;
    return it->second;
}

int main() {
    scanf("%d %d", &N, &M);
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        scanf("%d %d", &x, &y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x;
        scanf("%d", &op);
        switch(op) {
        case 0:
            scanf("%d", &x);
            UpdateHeavyPath(x);
            break;
        case 1:
            scanf("%d", &x);
            printf("%d\n", QueryHeavyPath(1, x));
            break;
        }
    }
    return 0;
}

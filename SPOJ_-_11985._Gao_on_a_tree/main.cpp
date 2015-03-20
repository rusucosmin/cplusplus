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

int heavy[MAXN], depth[MAXN];
int N, M, color[MAXN], pathWhere[MAXN], numPaths;
int pathFather[MAXN];
Graph G;
set < pair<int, int> > heavyPath[MAXN];

void DFs(int Node, int Father, int actLevel) {
    heavy[Node] = 1;
    depth[Node] = actLevel;
    int heaviest = -1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        DFs(*it, Node, actLevel + 1);
        if(heaviest == -1)
            heaviest = *it;
        else if(heavy[heaviest] < heavy[*it])
            heaviest = *it;
    }
    if(heaviest == -1) {
        pathWhere[Node] = ++ numPaths;
        heavyPath[pathWhere[Node]].clear();
        pathFather[pathWhere[Node]] = Father;
        heavyPath[pathWhere[Node]].insert(make_pair(color[Node], depth[Node]));
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    pathFather[pathWhere[Node]] = Father;
    heavyPath[pathWhere[Node]].insert(make_pair(color[Node], depth[Node]));
}

bool QueryHeavyPath(int x, int y, int c) {
    if(pathWhere[x] == pathWhere[y]) {
        if(depth[x] > depth[y])
            swap(x, y);
        set < pair<int, int> > :: iterator it = heavyPath[pathWhere[x]].lower_bound(make_pair(c, depth[x]));
        if(it == heavyPath[pathWhere[x]].end() || it -> first != c)
            return 0;
        if(depth[x] <= it->second && it->second <= depth[y])
            return 1;
    }
    if(pathFather[pathWhere[x]] < pathFather[pathWhere[y]])
        swap(x, y);
    bool actAns = 1;
    set<pair<int, int> > :: iterator it = heavyPath[pathWhere[x]].lower_bound(make_pair(c, 0));
    if(it == heavyPath[pathWhere[x]].end() || it->first != c || it->second > depth[x])
        actAns = 0;
    if(actAns)
        return 1;
    return QueryHeavyPath(pathFather[pathWhere[x]], y, c);
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    while(scanf("%d%d", &N, &M) == 2) {
        for(int i = 1 ; i <= N ; ++ i)
            scanf("%d", &color[i]);
        for(int i = 1 ; i != N ; ++ i) {
            int x, y;
            scanf("%d%d", &x, &y);
            G[x].push_back(y);
            G[y].push_back(x);
        }
        DFs(1, 0, 1);
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, c;
            scanf("%d%d%d", &x, &y, &c);
            bool Ans = QueryHeavyPath(x, y, c);
            if(Ans)
                printf("Find\n");
            else
                printf("NotFind\n");
        }
        printf("\n");
        numPaths = 0;
        for(int i = 1 ; i <= N ; ++ i)
            vector <int>().swap(G[i]);
    }
    return 0;
}

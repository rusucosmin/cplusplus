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

const char infile[] = "confuzie.in";
const char outfile[] = "confuzie.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 200005;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, numPaths;
int heavy[MAXN], depth[MAXN];
int pathWhere[MAXN], pathFather[MAXN];
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
        pathWhere[Node] = ++ numPaths;
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

int QueryHeavyPath(int x, int y) { /// x ancestor of y
    if(pathWhere[x] == pathWhere[y]) {
        set <pair<int, int> > :: iterator it = heavyPath[pathWhere[y]].lower_bound(make_pair(depth[x], x));
        if(it == heavyPath[pathWhere[y]].end() || it->first > depth[y])
            return -1;
        return it->second;
    }
    int actHighest = QueryHeavyPath(x, pathFather[pathWhere[y]]);
    if(actHighest != -1)
        return actHighest;
    set<pair<int, int> > :: iterator actMax = heavyPath[pathWhere[y]].begin();
    if(actMax == heavyPath[pathWhere[y]].end() || actMax -> first > depth[y])
        return -1;
    return actMax->second;
}

int main() {
    fin >> N >> M;
    for(int i = 1 ; i != N ; ++ i) {
        int x, y;
        fin >> x >> y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    DFs(1, 0, 1);
    for(int i = 1 ; i <= M ; ++ i) {
        int op, x, y;
        fin >> op;
        switch(op) {
        case 0:
            fin >> x;
            UpdateHeavyPath(x);
            break;
        case 1:
            fin >> x >> y;
            fout << QueryHeavyPath(x, y) << '\n';
            break;
        }
    }
    fin.close();
    fout.close();
    return 0;
}

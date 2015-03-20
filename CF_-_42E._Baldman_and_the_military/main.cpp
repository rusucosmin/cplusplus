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

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, Father[MAXN], value[MAXN];
Graph G;
vector <int> Path[MAXN], arb[MAXN];
vector <pair<int, pair<int, int> > > Edges;
int numPaths, pathWhere[MAXN], pathPosition[MAXN], pathFather[MAXN], depth[MAXN], heavy[MAXN];

inline int Find(int x) {
    if(Father[x] != x)
        Father[x] = Find(Father[x]);
    return Father[x];
}

inline void DFs(int Node, int Father, int actLevel) {
    depth[Node] = actLevel;
    heavy[Node] = 1;
    int heaviest = -1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
        if(!depth[it->first]) {
            DFs(it->first, Node, actLevel + 1);
            value[it->first] = it->second;
            heavy[Node] += heavy[it->first];
            if(heaviest == -1 || heavy[heaviest] < heavy[it->first])
                heaviest = it->first;
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

inline void Build(int Node, int st, int dr, int whichPath) {
    if(st == dr) {
        arb[whichPath][Node] = value[Path[whichPath][st]];
        return;
    }
    int mid = ((st + dr) >> 1);
    Build(Node << 1, st, mid, whichPath);
    Build((Node << 1) | 1, mid+1, dr, whichPath);
    arb[whichPath][Node] = max(arb[whichPath][Node << 1], arb[whichPath][(Node << 1) | 1]);
}

inline int Query(int Node, int st, int dr, int a, int b, int whichPath) {
    if(a <= st && dr <= b)
        return arb[whichPath][Node];
    int mid = ((st + dr) >> 1);
    int ansmax = -oo;
    if(a <= mid)
        ansmax = max(ansmax, Query(Node << 1, st, mid, a, b, whichPath));
    if(mid < b)
        ansmax = max(ansmax, Query((Node << 1) | 1, mid+1, dr, a, b, whichPath));
    return ansmax;
}

inline int QueryHeavyPath(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        if(pathPosition[x] > pathPosition[y])
            swap(x, y);
        if(pathPosition[x] == pathPosition[y])
            return 0;
        return Query(1, 0, Path[pathWhere[x]].size() - 1, pathPosition[x] + 1, pathPosition[y], pathWhere[x]);
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    int actMax = Query(1, 0, Path[pathWhere[x]].size() - 1, 0, pathPosition[x], pathWhere[x]);
    return max(QueryHeavyPath(pathFather[pathWhere[x]], y), actMax);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> M;
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        cin >> x >> y >> z;
        Edges.push_back(make_pair(z, make_pair(x, y)));
    }
    sort(Edges.begin(), Edges.end());
    int conn = N;
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    long long APM = 0;
    for(vector <pair<int, pair<int, int> > > :: iterator it = Edges.begin(), fin = Edges.end(); it != fin ; ++ it) {
        int z = it->first;
        int x = it->second.first;
        int y = it->second.second;
        int Tx = Find(x);
        int Ty = Find(y);
        if(Tx == Ty)
            continue;
        -- conn;
        Father[Tx] = Ty;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
        APM += z;
    }
    if(conn > 2) {
        cin >> M;
        for(int i = 1 ; i <= M ; ++ i)
            cout << "-1\n";
        return 0;
    }
    if(conn == 2) {
        cin >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            cin >> x >> y;
            if(Find(x) == Find(y))
                cout << "-1\n";
            else cout << APM << '\n';
        }
        return 0;
    }
    /// remain the conn == 1, cuz' it con't be 0
    cin >> M;
    /// prepare the HLD
    DFs(1, 0, 1);
    for(int i = 1 ; i <= numPaths ; ++ i) {
        reverse(Path[i].begin(), Path[i].end());
        for(int j = 0 ; j < int(Path[i].size()) ; ++ j)
            pathPosition[Path[i][j]] = j;
        arb[i].resize(Path[i].size() * 4 + 5);
        Build(1, 0, Path[i].size() - 1, i);
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y;
        cin >> x >> y;
        cout << APM - QueryHeavyPath(x, y) << '\n';
    }
    return 0;
}

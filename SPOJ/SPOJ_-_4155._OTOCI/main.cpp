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

const int MAXN = 33333;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

int N, M;
int penguins[MAXN];
int pathWhere[MAXN], pathPosition[MAXN], depth[MAXN], heavy[MAXN], numPaths, pathFather[MAXN];
vector <int> aib[MAXN];
vector <int> path[MAXN];
vector <pair<char, pair<int, int> > > Events;
int Father[MAXN];
Graph G;

int Find(int Node) {
    if(Father[Node] != Node)
        Father[Node] = Find(Father[Node]);
    return Father[Node];
}

void DFs(int Node, int dad, int actLevel) {
    heavy[Node] = 1;
    depth[Node] = actLevel;
    int heaviest = -1;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == dad)
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
        pathFather[pathWhere[Node]] = dad;
        path[pathWhere[Node]].push_back(Node);
        return;
    }
    pathWhere[Node] = pathWhere[heaviest];
    pathFather[pathWhere[Node]] = dad;
    path[pathWhere[Node]].push_back(Node);
}

inline int lsb(int conf) {
    return conf & (-conf);
}

inline void Update(int where, int Node, int value) {
    for(int i = Node ; i <= int(path[where].size()) ; i += lsb(i))
        aib[where][i] += value;
}

inline int Query(int where, int Node) {
    int sum = 0;
    for(int i = Node ; i > 0 ; i -= lsb(i))
        sum += aib[where][i];
    return sum;
}

inline int QueryHeavyPath(int x, int y) {
    if(pathWhere[x] == pathWhere[y]) {
        if(pathPosition[x] > pathPosition[y])
            swap(x, y);
        return (Query(pathWhere[x], pathPosition[y]) - Query(pathWhere[x], pathPosition[x] - 1));
    }
    if(depth[pathFather[pathWhere[x]]] < depth[pathFather[pathWhere[y]]])
        swap(x, y);
    int actsum = Query(pathWhere[x], pathPosition[x]) + QueryHeavyPath(pathFather[pathWhere[x]], y);
    return actsum;
}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    scanf("%d", &N);
    for(int i = 1 ; i <= N ; ++ i) {
        scanf("%d", &penguins[i]);
        Father[i] = i;
    }
    scanf("%d", &M);
    char a[20];
    int x, y;
    for(int i = 1 ; i <= M ; ++ i) {
        scanf("%s %d %d", &a, &x, &y);
        Events.push_back(make_pair(a[0], make_pair(x, y)));
        if(a[0] == 'b') {
            int Tx = Find(x);
            int Ty = Find(y);
            if(Tx == Ty)
                continue;
            G[x].push_back(y);
            G[y].push_back(x);
            Father[Tx] = Ty;
        }
    }
    DFs(1, 0, 1);
    for(int i = 1 ; i <= numPaths ; ++ i) {
        reverse(path[i].begin(), path[i].end());
        aib[i].resize(2 * path[i].size());
        for(int j = 0 ; j < int(path[i].size()) ; ++ j) {
            pathPosition[path[i][j]] = j + 1;
            Update(i, pathPosition[path[i][j]], penguins[path[i][j]]);
        }
    }
    for(int i = 1 ; i <= N ; ++ i)
        Father[i] = i;
    for(vector <pair<char, pair<int, int> > > :: iterator it = Events.begin(), fin = Events.end();
        it != fin ; ++ it) {
        if(it->first == 'b') {
            int Tx = Find(it->second.first);
            int Ty = Find(it->second.second);
            if(Tx == Ty) {
                printf("no\n");
                continue;
            }
            printf("yes\n");
            Father[Tx] = Ty;
        }
        if(it->first == 'p') {
            int delta = it->second.second - penguins[it->second.first];
            penguins[it->second.first] = it->second.second;
            Update(pathWhere[it->second.first], pathPosition[it->second.first], delta);
        }
        if(it->first == 'e') {
            int Tx = Find(it->second.first);
            int Ty = Find(it->second.second);
            if(Tx != Ty) {
                printf("impossible\n");
                continue;
            }
            printf("%d\n", QueryHeavyPath(it->second.first, it->second.second));
        }
    }
    return 0;
}


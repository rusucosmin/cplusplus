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

set<pair<int, int> > criticalEdges;
Graph G;
int N, depth[MAXN], lowlink[MAXN];

void DFs(int Node, int Father, int actLevel) {
    depth[Node] = lowlink[Node] = actLevel;
    for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
        if(*it == Father)
            continue;
        if(!depth[*it]) {
            DFs(*it, Node, actLevel + 1);
            lowlink[Node] = min(lowlink[Node], lowlink[*it]);
            if(lowlink[*it] > depth[Node])
                criticalEdges.insert(make_pair(min(Node, *it), max(Node, *it)));
        }
        else
            lowlink[Node] = min(lowlink[Node], depth[*it]);
    }

}

int main() {
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif // ONLINE_JUDGE
    while(scanf("%d", &N) == 1) {
        set<pair<int, int> > ().swap(criticalEdges);
        for(int i = 1 ; i <= N ; ++ i) {
            int x, y, z;
            scanf("%d (%d)", &x, &y);
            ++ x;
            depth[x] = 0;
            lowlink[x] = 0;
            vector <int> ().swap(G[x]);
            for(int j = 1 ; j <= y ; ++ j) {
                scanf("%d", &z);
                ++ z;
                G[x].push_back(z);
            }
        }
        for(int i = 1 ; i <= N ; ++ i)
            if(!depth[i])
                DFs(i, i, 1);
        printf("%d critical links\n", int(criticalEdges.size()));
        for(set<pair<int, int> > :: iterator it = criticalEdges.begin(), fin = criticalEdges.end(); it != fin ; ++ it)
            printf("%d - %d\n", it->first-1, it->second-1);
        printf("\n");
    }
    return 0;
}

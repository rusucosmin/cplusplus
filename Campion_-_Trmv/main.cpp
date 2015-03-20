#include <fstream>
#include <vector>
#include <bitset>
#include <stdio.h>
#include <queue>

using namespace std;

const char infile[] = "trmv.in";
const char outfile[] = "trmv.out";

const int MAXN = 1000005;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
vector <int> d(MAXN, oo);

inline void Dijkstra(const int &startNode) {
    priority_queue <pair<int, int> , vector<pair<int, int> > , greater <pair<int, int> > > Q;
    for(Q.push(make_pair(0, startNode)), d[startNode] = 0 ; !Q.empty() ; Q.pop()) {
        int Node = Q.top().second;
        if(d[Node] < Q.top().first)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(d[it->first] > d[Node] + it->second) {
                d[it->first] = d[Node] + it->second;
                Q.push(make_pair(d[it->first], it->first));
            }
    }
}

int main() {
    int N, T, S, P;
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d %d", &N, &T, &S, &P);
    for(int i = 1 ; i <= T ; ++ i) {
        int x, last = -1;
        scanf("%d", &x);
        for(int i = 1 ; i <= x ; ++ i) {
            if(last == -1) {
                scanf("%d", &last);
                continue;
            }
            int cost, x;
            scanf("%d %d", &cost, &x);
            G[last].push_back(make_pair(x, cost));
            G[x].push_back(make_pair(last, cost));
            swap(x, last);
        }
    }
    Dijkstra(S);
    for(int i = 1 ; i <= P ; ++ i) {
        int x;
        scanf("%d", &x);
        printf("%d ", d[x] == oo ? -1 : d[x]);
    }
    return 0;
}

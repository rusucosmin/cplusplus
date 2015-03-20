#include <vector>
#include <bitset>
#include <queue>
#include <string.h>
#include <stdio.h>

using namespace std;

const char infile[] = "zmeu.in";
const char outfile[] = "zmeu.out";

const int MAXN = 1005;
const int oo = 0x3f3f3f3f;

typedef vector< pair<int, int> > Graph[MAXN];
typedef vector< pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, P, K = 5;/// k - nr printises
int v[7];
int d[7][7], best[MAXN], dp[1 << 7][MAXN];
int nearestExit[MAXN];
Graph G;

inline void Dijkstra(const int &startNode) {
    memset(best, oo, sizeof(best));
    priority_queue <pair<int, int>, vector< pair<int, int> > , greater <pair<int, int> > > Q;
    for(Q.push(make_pair(0, startNode)), best[startNode] = 0 ; !Q.empty() ; Q.pop()) {
        int Node = Q.top().second;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(best[it->first] > best[Node] + it->second) {
                best[it->first] = best[Node] + it->second;
                Q.push(make_pair(best[it->first], it->first));
            }
    }
}

inline void buildDistancesFromExit() {
    queue <int> Q;
    memset(nearestExit, oo, sizeof(nearestExit));
    for(int i = 1 ; i <= P ; ++ i) {
        int x;
        scanf("%d ", &x);
        -- x;
        Q.push(x);
        nearestExit[x] = 0;
    }
    for( ; !Q.empty() ; Q.pop()) {
        int Node = Q.front();
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(nearestExit[it->first] > nearestExit[Node] + it->second) {
                nearestExit[it->first] = nearestExit[Node] + it->second;
                Q.push(it->first);
            }
    }
}

int main() {
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    scanf("%d %d %d", &N, &M, &P);
    for(int i = 0 ; i <= K ; ++ i) {
        scanf("%d", &v[i]);
        -- v[i];
    }
    for(int i = 1 ; i <= M ; ++ i) {
        int x, y, z;
        scanf("%d %d %d", &x, &y, &z);
        -- x;
        -- y;
        G[x].push_back(make_pair(y, z));
        G[y].push_back(make_pair(x, z));
    }
    /****
        Mai intai d[i][j] = distanta minimima de la printesa i la printesa j
    */
    for(int i = 0 ; i <= K ; ++ i) {
        Dijkstra(v[i]);
        for(int j = 0 ; j <= K ; ++ j)
            d[i][j] = best[v[j]];
    }
    buildDistancesFromExit();
    ++ K;
    int maxConf = (1 << K);
    memset(dp, oo, sizeof(dp));
    dp[1][0] = 0;
    for(int conf = 1 ; conf < maxConf ; ++ conf)
        for(int i = 0 ; i < K ; ++ i)
            if(conf & ( 1 << i ))
                for(int j = 0 ; j < K ; ++ j)
                    if(conf & ( 1 << j ))
                        dp[conf][i] = min(dp[conf][i], dp[conf ^ ( 1 << i )][j] + d[j][i]);
    int Ans = oo;
    for(int i = 0 ; i < K ; ++ i)
        Ans = min(Ans, dp[maxConf - 1][i] + nearestExit[v[i]]);
    printf("%d", Ans);
    return 0;
}

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

const int MAXN = 415;
const int oo = 0x3f3f3f3f;

typedef vector< int > Graph[MAXN];
typedef vector< int > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int T, N, M, C[MAXN][MAXN], cost[MAXN][MAXN], Father[MAXN];
int dp[MAXN];
Graph G;
queue <int> Q;
bitset <MAXN> inQ;

inline bool BF(Graph &G, int Source, int Sink) {
    memset(dp, oo, sizeof(dp));
    dp[Source] = 0;
    Q.push(Source);
    inQ[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = 0;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(C[Node][*it] > 0 && dp[*it] > dp[Node] + cost[Node][*it]) {
                dp[*it] = dp[Node] + cost[Node][*it];
                Father[*it] = Node;
                if(inQ[*it])
                    continue;
                Q.push(*it);
                inQ[*it] = 1;
            }
    }
    return dp[Sink] != oo;
}

inline pair<int, int> getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    int minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        maxFlow += bottleNeck;
        minCostMaxFlow += bottleNeck * dp[Sink];
    }
    return make_pair(maxFlow, minCostMaxFlow);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    for(scanf("%d", &T) ; T -- ; ) {
        scanf("%d%d", &N, &M);
        int Source = 0, Sink = 2 * N + 1;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            G[x].push_back(y + N);
            C[x][y + N] = 1;
            cost[x][y + N] = z;
            G[y + N].push_back(x);
            cost[y + N][x] = -z;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            G[Source].push_back(i);
            G[i].push_back(Source);
            C[Source][i] = 1;
            G[i + N].push_back(Sink);
            G[Sink].push_back(i + N);
            C[i + N][Sink] = 1;
        }
        pair<int, int> Ans = getMinCostMaxFlow(G, Source, Sink);
        if(Ans.first != N)
            printf("Impossible\n");
        else printf("%d\n", Ans.second);
        memset(C, 0, sizeof(C));
        memset(cost, 0, sizeof(cost));
        for(int i = Source ; i <= Sink ; ++ i)
            vector < int > ().swap(G[i]);
    }
    fin.close();
    fout.close();
    return 0;
}

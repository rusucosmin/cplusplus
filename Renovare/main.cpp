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

const char infile[] = "renovare.in";
const char outfile[] = "renovare.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 405;
const int MAXM = 2005;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M, X;
int C[4 * MAXM], cost[4 * MAXM], dp[MAXN], Father[MAXN], Source, F[4 * MAXM];
int dad[MAXN];
Graph G;
queue <int> Q;
bitset <MAXN> inQ;

inline bool BF(Graph &G, int Source, int Sink) {
    for(int i = 1 ; i <= N ; ++ i)
        dp[i] = oo;
    dp[Source] = 0;
    Q.push(Source);
    inQ[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = 0;
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(C[it->second] - F[it->second] > 0 && dp[it->first] > dp[Node] + cost[it->second]) {
                dp[it->first] = dp[Node] + cost[it->second];
                Father[it->first] = it->second;
                dad[it->first] = Node;
                if(inQ[it->first])
                    continue;
                Q.push(it->first);
                inQ[it->first] = 1;
            }
        }
    }
    return (dp[Sink] != oo);
}

inline int getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = dad[i])
            bottleNeck = min(bottleNeck, C[Father[i]] - F[Father[i]]);
        for(int i = Sink ; i != Source ; i = dad[i]) {
            F[Father[i]] += bottleNeck;
            F[Father[i] ^ 1] -= bottleNeck;
        }
        minCostMaxFlow += bottleNeck * dp[Sink];
    }
    return minCostMaxFlow;
}

int main() {
    fin >> N >> M >> X;
    int Edge = -1;
    for(int i = 1 ; i <= M ; ++ i) {
        int a, b, c, d; /// x -> y capacity cost
        fin >> a >> b >> c >> d;

        ++ Edge;
        G[a].push_back(make_pair(b, Edge));
        C[Edge] = c;

        ++ Edge;
        G[b].push_back(make_pair(a, Edge));

        ++ Edge;
        G[a].push_back(make_pair(b, Edge));
        C[Edge] = oo;
        cost[Edge] = d;

        ++ Edge;
        G[b].push_back(make_pair(a, Edge));
        cost[Edge] = -d;
    }
    Source = 0;
    ++ Edge;
    G[Source].push_back(make_pair(1, Edge));
    C[Edge] = X;
    ++ Edge;
    G[1].push_back(make_pair(Source, Edge));
    fout << getMinCostMaxFlow(G, Source, N) << '\n';
    fin.close();
    fout.close();
    return 0;
}

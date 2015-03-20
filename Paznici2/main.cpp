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

const char infile[] = "paznici2.in";
const char outfile[] = "paznici2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 405;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int Father[MAXN], C[MAXN][MAXN], dp[MAXN];
int cost[MAXN][MAXN];
bitset <MAXN> inQ;
queue <int> Q;

inline bool BF(Graph &G, int Source, int Sink) {
    memset(dp, oo, sizeof(dp));
    Q.push(Source);
    inQ[Source] = 1;
    dp[Source] = 0;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = 0;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(C[Node][it->first] > 0 && dp[it->first] > dp[Node] + it->second) {
                dp[it->first] = dp[Node] + it->second;
                Father[it->first] = Node;
                if(inQ[it->first])
                    continue;
                Q.push(it->first);
                inQ[it->first] = 1;
            }
        }
    }
    return dp[Sink] != oo;
}

inline int getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0, minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        maxFlow += bottleNeck;
        minCostMaxFlow += dp[Sink];
    }
    return minCostMaxFlow;
}

int main() {
    int N, Source, Sink;
    fin >> N;
    Source = 0;
    Sink = 2 * N + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = N + 1 ; j <= N + N ; ++ j) {
            int x;
            fin >> x;
            cost[i][j] = x;
            G[i].push_back(make_pair(j, x));
            G[j].push_back(make_pair(i,-x));
            C[i][j] = 1;
        }
        G[Source].push_back(make_pair(i, 0));
        G[i].push_back(make_pair(Source, 0));
        C[Source][i] = 1;
        G[i + N].push_back(make_pair(Sink, 0));
        G[Sink].push_back(make_pair(i + N, 0));
        C[i + N][Sink] = 1;
    }
    fout << getMinCostMaxFlow(G, Source, Sink) << '\n';
    for(int i = 1 + N ; i <= N + N ; ++ i) {
        BF(G, i, Sink);
        vector <int> Ans;
        for(int j = 1 ; j <= N ; ++ j)
            if(dp[j] + cost[j][i] == 0)
                Ans.push_back(j);
        fout << Ans.size() << ' ';
        for(auto it : Ans)
            fout << it << ' ';
        fout << '\n';
    }
    fin.close();
    fout.close();
    return 0;
}

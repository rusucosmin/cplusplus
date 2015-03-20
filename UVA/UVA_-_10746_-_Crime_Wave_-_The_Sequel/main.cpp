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

const int MAXN = 50;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
double cost[MAXN][MAXN], dp[MAXN];
Graph G;
int Father[MAXN], C[MAXN][MAXN];
queue <int> Q;
bitset <MAXN> inQ;

inline bool BF(Graph &G, int Source, int Sink) {
    for(int i = Source ; i <= Sink ; ++ i)
        dp[i] = 10000000.0;
    Q.push(Source);
    dp[Source] = 0;
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
    return dp[Sink] != 10000000.0;
}

inline double getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    double minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        for(int i = Sink ; i != Source ; i = Father[i]) {
            -- C[Father[i]][i];
            ++ C[i][Father[i]];
        }
        minCostMaxFlow += dp[Sink];
    }
    return minCostMaxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N >> M) {
        if(!N && !M)
            return 0;
        int Source = 0;
        int Sink = N + M + 1;
        for(int i = 1 ; i <= N ; ++ i) {
            for(int j = N + 1 ; j <= N + M ; ++ j) {
                cin >> cost[i][j];
                cost[j][i] = -cost[i][j];
                G[i].push_back(j);
                G[j].push_back(i);
                C[i][j] = 1;
            }
            G[Source].push_back(i);
            G[i].push_back(Source);
            C[Source][i] = 1;
        }
        for(int i = N + 1 ; i <= N + M ; ++ i) {
            G[i].push_back(Sink);
            G[Sink].push_back(i);
            C[i][Sink] = 1;
        }
        double flowCost = getMinCostMaxFlow(G, Source, Sink) / N;
        flowCost = floor(flowCost*100.0+0.5+1e-9)/100.0;
        cout << fixed << setprecision(2) << flowCost  << '\n';
        for(int i = Source ; i <= Sink ; ++ i)
            vector <int> ().swap(G[i]);
        memset(C, 0, sizeof(C));
        memset(cost, 0, sizeof(cost));
    }
    fin.close();
    fout.close();
    return 0;
}

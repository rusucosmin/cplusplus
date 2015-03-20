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

const int MAXN = 805;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

pair<int, int> P[MAXN];
int C[MAXN][MAXN], Father[MAXN];
double cost[MAXN][MAXN], dp[MAXN];
queue <int> Q;
bitset <MAXN> inQ;
Graph G;

inline bool BF(Graph &G, int Source, int Sink) {
    for(int i = Source ; i <= Sink ; ++ i)
        dp[i] = 100000000.0;
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
    return dp[Sink] != 100000000.0;
}

inline pair<int, double> getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0; double minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        for(int i = Sink ; i != Source ; i = Father[i]) {
            -- C[Father[i]][i];
            ++ C[i][Father[i]];
        }
        ++ maxFlow;
        minCostMaxFlow += dp[Sink];
    }
    return make_pair(maxFlow, minCostMaxFlow);
}

inline int sqr(int x) {
    return x * x;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    int N, Source, Sink;
    cin >> N;
    Source = 0; Sink = 2 * N + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        G[Source].push_back(i);
        G[i].push_back(Source);

        C[Source][i] = 2;

        G[i + N].push_back(Sink);
        G[Sink].push_back(i + N);

        C[i + N][Sink] = 1;

        cin >> P[i].first >> P[i].second;
    }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= N ; ++ j) {
            if(P[i].second > P[j].second) {
                G[i].push_back(j + N);
                G[j + N].push_back(i);
                C[i][j + N] = 1;
                double z = sqrt(1.0 * sqr(P[i].first - P[j].first) + 1.0 * sqr(P[i].second - P[j].second));
                ///cerr << z << '\n';
                cost[i][j + N] = z;
                cost[j + N][i] = -z;
            }
        }
    }
    pair<int, double> Ans = getMinCostMaxFlow(G, Source, Sink);
    if(Ans.first != N - 1) {
        cout << "-1\n";
        return 0;
    }
    else cout << fixed << setprecision(10) << Ans.second << '\n';
    return 0;
}

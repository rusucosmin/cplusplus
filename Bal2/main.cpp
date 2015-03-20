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

const char infile[] = "bal2.in";
const char outfile[] = "bal2.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 505;
const double oo = 0x3f3f3f3f;
const double EPS = 0.000001;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N;
int K, C[MAXN][MAXN];
double dp[MAXN], cost[MAXN][MAXN];
int Father[MAXN];
queue <int> Q;
Graph G;
bitset <MAXN> inQ;

inline bool BF(Graph &G, int Source, int Sink) {
    for(int i = 0 ; i <= 2 * N + 1 ; ++ i)
        dp[i] = 1000000000.0;
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
    return (dp[Sink] != 1000000000.0);
}

inline double getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    double minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        minCostMaxFlow += dp[Sink];
    }
    //cerr << minCostMaxFlow << '\n';
    return minCostMaxFlow;
}

int main() {
    fin >> N >> K;
    int Source = 0, Sink = 2*N + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= N ; ++ j) {
            double x;
            fin >> x;
            G[i].push_back(j + N);
            cost[i][j + N] = -log10(x / 100.0);
            C[i][j + N] = 1;
            G[j + N].push_back(i);
            cost[j + N][i] = log10(x / 100.0);
        }
        G[Source].push_back(i);
        C[Source][i] = K;
        G[i].push_back(Source);
        G[i + N].push_back(Sink);
        C[i + N][Sink] = 1;
        G[Sink].push_back(i + N);
    }
    fout << fixed << setprecision(2) << pow(10, -getMinCostMaxFlow(G, Source, Sink)) * 100 << '\n';
    fin.close();
    fout.close();
    return 0;
}

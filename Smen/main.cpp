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

const char infile[] = "smen.in";
const char outfile[] = "smen.out";

ifstream fin(infile);
ofstream fout(outfile);

const int MAXN = 605;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int C[MAXN][MAXN], F[MAXN][MAXN], Father[MAXN], dp[MAXN], N, K, A, B, Source, Sink;
int cost[MAXN][MAXN];
int a[MAXN];
bitset <MAXN> inQ;
queue <int> Q;
Graph G;

inline bool BF(Graph &G, int Source, int Sink) {
    memset(dp, oo, sizeof(dp));
    dp[Source] = 0;
    Q.push(Source);
    inQ[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = false;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(C[Node][*it] - F[Node][*it] > 0 && dp[*it] > dp[Node] + cost[Node][*it]) {
                dp[*it] = dp[Node] + cost[Node][*it];
                Father[*it] = Node;
                if(inQ[*it])
                    continue;
                Q.push(*it);
                inQ[*it] = 1;
            }
    }
    return (dp[Sink] != oo);
}

inline int getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i] - F[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            F[Father[i]][i] += bottleNeck;
            F[i][Father[i]] -= bottleNeck;
        }
        minCostMaxFlow += bottleNeck * dp[Sink];
    }
    return minCostMaxFlow;
}

inline int myAbs(int x) {
    return max(x, -x);
}

int main() {
    fin >> N >> K >> A >> B;
    A += 201;
    B += 201;
    Source = 0;
    Sink = B + N + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        int x;
        fin >> x;
        a[i] = x;
        for(int j = A ; j <= B ; ++ j) {
            G[i].push_back(j + N);
            G[j + N].push_back(i);
            C[i][j + N] = 1;
            cost[i][j + N] = myAbs((j - 201) - x);
            cost[j + N][i] = -myAbs((j - 201) - x);
        }
        G[Source].push_back(i);
        G[i].push_back(Source);
        C[Source][i] = 1;
    }
    for(int j = A ; j <= B ; ++ j) {
        G[j + N].push_back(Sink);
        G[Sink].push_back(j + N);
        C[j + N][Sink] = 1;
    }
    G[Sink].push_back(Sink + 1);
    G[Sink + 1].push_back(Sink);
    C[Sink][Sink + 1] = K;
    fout << getMinCostMaxFlow(G, Source, Sink + 1) << '\n';
    for(int i = 1 ; i <= N ; ++ i) {
        bool ok = false;
        for(int j = A + N ; j <= B + N && !ok ; ++ j)
            if(F[i][j]) {
                fout << a[i] + cost[i][j] << ' ';
                ok = true;
            }
        if(!ok)
            fout << a[i] << ' ';
    }
    fin.close();
    fout.close();
    return 0;
}

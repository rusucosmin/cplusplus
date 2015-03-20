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

const int MAXN = 1050;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int C[MAXN][MAXN], Father[MAXN], cost[MAXN][MAXN], N, B, Source, Sink;
int F[MAXN][MAXN];
bitset <MAXN> inQ;
queue <int> Q;
Graph G;

inline bool BFs(Graph &G, int Source, int Sink, int st, int dr) {
    inQ.reset();
    Q.push(Source);
    inQ[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it)
            if(!inQ[*it] && C[Node][*it] - F[Node][*it] > 0 && (cost[Node][*it] == oo || (st <= cost[Node][*it] && cost[Node][*it] <= dr))) {
                Father[*it] = Node;
                Q.push(*it);
                inQ[*it] = 1;
            }
    }
    return inQ[Sink];
}

inline int getMaxFlow(Graph &G, int Source, int Sink, int st, int dr) {
    int maxFlow = 0;
    while(BFs(G, Source, Sink, st, dr)) {
        for(It it = G[Sink].begin(), fin = G[Sink].end(); it != fin ; ++ it) {
            if(!(inQ[*it] && C[*it][Sink] - F[*it][Sink] > 0 && (cost[*it][Sink] == oo || (st <= cost[*it][Sink] && cost[*it][Sink] <= dr))))
                continue;
            Father[Sink] = *it;
            int bottleNeck = oo;
            for(int i = Sink ; i != Source ; i = Father[i])
                bottleNeck = min(bottleNeck, C[Father[i]][i] - F[Father[i]][i]);
            if(!bottleNeck)
                continue;
            for(int i = Sink ; i != Source ; i = Father[i]) {
                F[Father[i]][i] += bottleNeck;
                F[i][Father[i]] -= bottleNeck;
            }
            maxFlow += bottleNeck;
        }
    }
    return maxFlow;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> B;
    Source = 0;
    Sink = N + B + 1;
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = 1 ; j <= B ; ++ j) {
            int x;
            cin >> x;
            G[i].push_back(x + N);
            G[x + N].push_back(i);
            C[i][x + N] = 1;
            cost[i][x + N] = j;
            cost[x + N][i] = oo;
        }
        G[Source].push_back(i);
        G[i].push_back(Source);
        C[Source][i] = 1;
    }
    for(int j = 1 ; j <= B ; ++ j) {
        int x;
        cin >> x;
        G[j + N].push_back(Sink);
        G[Sink].push_back(j + N);
        C[j + N][Sink] = x;
        cost[j + N][Sink] = oo;
        cost[Sink][j + N] = oo;
    }
    int Ans = B;
    for(int i = 1 ; i <= B ; ++ i)
        for(int j = i + 1 ; j <= B ; ++ j) {
                memset(F, 0, sizeof(F));
                if(getMaxFlow(G, Source, Sink, i, j) == N) {
                    Ans = min(Ans, j - i + 1);
                    break;
                }
            }
    cout << Ans << '\n';
    return 0;
}

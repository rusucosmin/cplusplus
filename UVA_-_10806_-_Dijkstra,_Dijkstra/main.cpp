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

const int MAXN = 205;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

queue <int> Q;
int N, M, cost[MAXN][MAXN], C[MAXN][MAXN], dp[MAXN], Father[MAXN];
int Source, Sink;
bitset <MAXN> inQ;
Graph G;

inline int in(int x) {
    return x;
}

inline int out(int x) {
    return x + N;
}

inline bool BellmanFord(Graph &G, int Source, int Sink) {
    inQ.reset();
    memset(dp, oo, sizeof(dp));
    Q.push(Source);
    inQ[Source] = 1;
    dp[Source] = 0;
    while(!Q.empty()) {
        int Node = Q.front();
        ///cerr << Node << '\n';
        Q.pop();
        inQ[Node] = false;
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(C[Node][*it] > 0 && dp[*it] > dp[Node] + cost[Node][*it]) {
                dp[*it] = dp[Node] + cost[Node][*it];
                Father[*it] = Node;
                if(inQ[*it])
                    continue;
                Q.push(*it);
                inQ[*it] = 1;
            }
        }
    }
    return dp[Sink] != oo;
}

inline pair<int, int> getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int minCostMaxFlow = 0;
    int maxFlow = 0;
    while(BellmanFord(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        if(!bottleNeck)
            continue;
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        maxFlow += bottleNeck;
        minCostMaxFlow += dp[Sink];
    }
    return make_pair(maxFlow, minCostMaxFlow);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N) {
        if(!N)
            return 0;
        Source = 0;
        Sink = 2 * N + 1;
        cin >> M;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            G[out(x)].push_back(in(y));
            G[in(y)].push_back(out(x));
            C[out(x)][in(y)] = 1;
            cost[out(x)][in(y)] = z;
            cost[in(y)][out(x)]= -z;
            G[out(y)].push_back(in(x));
            G[in(x)].push_back(out(y));
            C[out(y)][in(x)] = 1;
            cost[out(y)][in(x)] = z;
            cost[in(x)][out(y)] = -z;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            C[in(i)][out(i)] = oo;
            G[in(i)].push_back(out(i));
            G[out(i)].push_back(in(i));
        }
        Source = 0;
        G[Source].push_back(in(1));
        G[in(1)].push_back(Source);
        C[Source][in(1)] = 2;
        G[out(N)].push_back(Sink);
        G[Sink].push_back(out(N));
        C[out(N)][Sink] = 2;
        pair<int, int> Ans = getMinCostMaxFlow(G, Source, Sink);
        if(Ans.first == 2)
            cout << Ans.second << '\n';
        else
            cout << "Back to jail\n";
        memset(C, 0, sizeof(C));
        memset(cost, 0, sizeof(cost));
        for(int i = Source ; i <= Sink ; ++ i)
            vector <int>().swap(G[i]);
    }
    return 0;
}

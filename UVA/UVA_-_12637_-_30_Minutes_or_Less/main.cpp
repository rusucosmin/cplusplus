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

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int dp[MAXN], C[MAXN][MAXN], Father[MAXN], R, N;
pair<int, int> P[MAXN];
bitset <MAXN> inQ;
queue <int> Q;
Graph G;

inline int myAbs(int x) {
    if(x > 0)
        return x;
    return -x;
}

inline int manhattanDistance(int x1, int y1, int x2, int y2) {
    return myAbs(x1 - x2) + myAbs(y1 - y2);
}

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
            if(C[Node][it->first] > 0 && dp[it->first] > dp[Node] + it->second) {
                dp[it->first] = dp[Node] + it->second;
                Father[it->first] = Node;
                if(inQ[it->first])
                    continue;
                Q.push(it->first);
                inQ[it->first] = 1;
            }
    }
    return dp[Sink] != oo;
}

inline int getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int minCostMaxFlow = 0;
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
    while(cin >> R >> N) {
        int Source = 0, Sink = R + N + 1;
        for(int i = 1 ; i <= R ; ++ i) {
            cin >> P[i].first >> P[i].second;
            G[Source].push_back(make_pair(i, 0));
            G[i].push_back(make_pair(Source, 0));
            C[Source][i] = 1;
        }
        for(int i = R + 1 ; i <= R + N ; ++ i) {
            int x, y;
            cin >> x >> y;
            G[i].push_back(make_pair(Sink, 0));
            G[Sink].push_back(make_pair(i, 0));
            C[i][Sink] = 1;
            for(int j = 1 ; j <= R ; ++ j) {
                G[j].push_back(make_pair(i, manhattanDistance(P[j].first, P[j].second, x, y)));
                G[i].push_back(make_pair(j, -manhattanDistance(P[j].first, P[j].second, x, y)));
                C[j][i] = 1;
            }
        }
        cout << getMinCostMaxFlow(G, Source, Sink) << '\n';
        memset(C, 0, sizeof(C));
        for(int i = Source ; i <= Sink ; ++ i)
            vector <pair<int, int> > ().swap(G[i]);
    }
    return 0;
}

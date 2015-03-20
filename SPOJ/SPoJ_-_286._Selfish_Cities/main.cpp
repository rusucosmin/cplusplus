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

const int MAXN = 105;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[2*MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int C[2*MAXN][2*MAXN], Cost[2*MAXN][2*MAXN], N, M, T;
int Father[2*MAXN];
int Source, Sink;
int dp[2*MAXN];
bitset <2*MAXN> inQ;
queue <int> Q;

inline bool Dijkstra(int Source, int Sink) {
    memset(dp, oo, sizeof(dp));
    dp[Source] = 0;
    Q.push(Source);
    inQ[Source] = true;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = false;
        if(Node == Sink)
            continue;
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(C[Node][*it] > 0 && dp[*it] > dp[Node] + Cost[Node][*it]) {
                dp[*it] = dp[Node] + Cost[Node][*it];
                Father[*it] = Node;
                if(!inQ[*it]) {
                    inQ[*it] = 1;
                    Q.push(*it);
                }
            }
        }
    }
    return dp[Sink] != oo;
}

inline int maximumCostMaximumMatching(Graph &G, int Source, int Sink) {
    int maximumMatching = 0;
    int maximumCostMatching = 0;
    while(Dijkstra(Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        maximumMatching += bottleNeck;
        maximumCostMatching += dp[Sink];
    }
    return maximumCostMatching;
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    for(cin >> T ; T -- ; ) {
        cin >> N >> M;
        Source = 0; Sink = N + M + 1;
        int x, y, z;
        while(cin >> x >> y >> z) {
            if(!x && !y && !z)
                break;
            G[x].push_back(y + N);
            G[y + N].push_back(x);
            Cost[x][y + N] = -z;
            Cost[y + N][x] = z;
            C[x][y + N] = 1;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            G[Source].push_back(i);
            G[i].push_back(Source);
            C[Source][i] = 1;
        }
        for(int i = N + 1 ; i <= N + M ; ++ i) {
            G[i].push_back(Sink);
            G[Sink].push_back(i);
            C[i][Sink] = 1;
        }
        cout << -maximumCostMaximumMatching(G, Source, Sink) << '\n';
        memset(Cost, 0, sizeof(Cost));
        memset(C, 0, sizeof(C));
        for(int i = Source; i <= Sink ; ++ i)
            vector <int> ().swap(G[i]);
    }
    return 0;
}

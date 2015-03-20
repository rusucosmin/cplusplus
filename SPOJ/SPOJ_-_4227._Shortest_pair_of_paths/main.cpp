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
const int MAXM = 1000;
const int oo = 0x3f3f3f3f;

typedef vector<pair<int, int> > Graph[MAXN];
typedef vector<pair<int, int> > :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int C[MAXM], cost[MAXM], dad[MAXN], Father[MAXN], dp[MAXN], N, M;
queue <int> Q;
bitset <MAXN> inQ;

inline int in(int x) {
    return x;
}

inline int out(int x) {
    return x + N;
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
        for(It it = G[Node].begin(), fin = G[Node].end(); it != fin ; ++ it) {
            if(C[it->second] > 0 && dp[it->first] > dp[Node] + cost[it->second]) {
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

inline pair<int, int> getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int minCostMaxFlow = 0;
    int maxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = dad[i])
            bottleNeck = min(bottleNeck, C[Father[i]]);
        for(int i = Sink ; i != Source ; i = dad[i]) {
            C[Father[i]] -= bottleNeck;
            C[Father[i] ^ 1] += bottleNeck;
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
    for(int test = 1 ; cin >> N >> M ; ++ test) {
        if(!N && !M)
            return 0;
        int Edge = -1;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y, z;
            cin >> x >> y >> z;
            ++ x;
            ++ y;
            if(x == y)
                continue;
            G[out(x)].push_back(make_pair(in(y), ++ Edge));
            C[Edge] = 1;
            cost[Edge] = z;
            G[in(y)].push_back(make_pair(out(x), ++ Edge));
            cost[Edge] = -z;
        }
        for(int i = 1 ; i <= N ; ++ i) {
            G[in(i)].push_back(make_pair(out(i), ++ Edge));
            C[Edge] = 1;
            G[out(i)].push_back(make_pair(in(i), ++ Edge));
        }
        G[0].push_back(make_pair(out(1), ++ Edge));
        C[Edge] = 2;
        G[out(1)].push_back(make_pair(0, ++ Edge));
        pair<int, int> Ans = getMinCostMaxFlow(G, 0, in(N));
        cout << "Instance #" << test << ":  ";
        if(Ans.first != 2)
            cout << "Not possible";
            else cout << Ans.second;
        cout << "\n";
        memset(cost, 0, sizeof(cost));
        memset(C, 0, sizeof(C));
        for(int i = 0 ; i <= 2 * N + 1 ; ++ i)
            vector <pair<int, int> > ().swap(G[i]);
    }
    return 0;
}

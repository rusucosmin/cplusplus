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
const long long oo = 1000000000000000000LL;

typedef vector<int> Graph[MAXN];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

int N, M;
long long D, K;
long long C[MAXN][MAXN];
long long dp[MAXN], cost[MAXN][MAXN];
int Source, Sink;
int Father[MAXN];
vector <pair<int, int> > v;
bitset <MAXN> inQ;
queue <int> Q;
Graph G;

inline int in(int x) {
    return x;
}

inline int out(int x) {
    return x + N;
}

inline bool BF(int Source, int Sink) { /// BellmanFord
    for(int i = Source ; i <= Sink ; ++ i)
        dp[i] = oo;
    Q.push(Source);
    inQ[Source] = 1;
    dp[Source] = 0;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = 0;
        if(Node == Sink)
            continue;
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
    return (dp[Sink] != oo);
}

inline pair<long long, long long> getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    long long maxFlow = 0;
    long long minCostMaxFlow = 0;
    while(BF(Source, Sink)) {
        long long bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i]);
        for(int i = Sink ; i != Source ; i = Father[i]) {
            C[Father[i]][i] -= bottleNeck;
            C[i][Father[i]] += bottleNeck;
        }
        maxFlow += bottleNeck;
        minCostMaxFlow += bottleNeck * dp[Sink];
    }
    return make_pair(maxFlow, minCostMaxFlow);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    while(cin >> N >> M) {
        Source = 0;
        Sink = 2 * N + 1;
        for(int i = 1 ; i <= M ; ++ i) {
            int x, y;
            long long z;
            cin >> x >> y >> z;
            if(x == y)
                continue;
            G[out(x)].push_back(in(y));
            G[in(y)].push_back(out(x));

            G[out(y)].push_back(in(x));
            G[in(x)].push_back(out(y));

            v.push_back(make_pair(x, y));

            cost[out(x)][in(y)] = z;
            cost[in(y)][out(x)] = -z;
            cost[out(y)][in(x)] = z;
            cost[in(x)][out(y)] = -z;
        }
        cin >> D >> K;
        for(vector <pair<int, int> > :: iterator it = v.begin(), fin = v.end(); it != fin ; ++ it) {
            C[out(it->first)][in(it->second)] = K;
            C[out(it->second)][in(it->first)] = K;
        }
        G[Source].push_back(in(1));
        G[in(1)].push_back(Source);
        C[Source][in(1)] = D;

        for(int i = 1 ; i <= N ; ++ i) {
            G[in(i)].push_back(out(i));
            G[out(i)].push_back(in(i));
            C[in(i)][out(i)] = oo;
        }
        G[out(N)].push_back(Sink);
        G[Sink].push_back(out(N));
        C[out(N)][Sink] = D;
        pair<long long, long long> minCostMaxFlow = getMinCostMaxFlow(G, Source, Sink);
        if(minCostMaxFlow.first != D)
            cout << "Impossible.\n";
        else cout << minCostMaxFlow.second << '\n';

        memset(C, 0, sizeof(C));
        memset(cost, 0, sizeof(cost));
        vector <pair<int, int> > ().swap(v);
        for(int i = Source ; i <= Sink ; ++ i)
            vector <int>().swap(G[i]);
    }
    return 0;
}

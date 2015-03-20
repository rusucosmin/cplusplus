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

const int MAXN = 255;
const int MAXM = 27;
const int oo = 0x3f3f3f3f;

typedef vector<int> Graph[2 * MAXN + MAXM];
typedef vector<int> :: iterator It;

const inline int min(const int &a, const int &b) { if( a > b ) return b;   return a; }
const inline int max(const int &a, const int &b) { if( a < b ) return b;   return a; }
const inline void Get_min(int &a, const int b)    { if( a > b ) a = b; }
const inline void Get_max(int &a, const int b)    { if( a < b ) a = b; }

Graph G;
int N, M, A[MAXN];
int cost[2 * MAXN + MAXM][2 * MAXN + MAXM], nrBits[MAXN], dp[2 * MAXN + MAXM];
bitset <2 * MAXN + MAXM > inQ;
queue <int> Q;
int Father[2 * MAXN + MAXM];
int C[2 * MAXN + MAXM][2 * MAXN + MAXM];
int F[2 * MAXN + MAXM][2 * MAXN + MAXM];
int mate[2*MAXN + MAXM];
int match[2*MAXN + MAXM];
int val[MAXM];

inline int bitCount(int x) {
    int ret = 0;
    while(x) {
        x &= (x - 1);
        ++ ret;
    }
    return ret;
}

inline bool BF(Graph &G, int Source, int Sink) {
    memset(dp, oo, sizeof(dp));
    Q.push(Source);
    dp[Source] = 0;
    inQ[Source] = 1;
    while(!Q.empty()) {
        int Node = Q.front();
        Q.pop();
        inQ[Node] = 0;
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
    return dp[Sink] != oo;
}

inline int getMinCostMaxFlow(Graph &G, int Source, int Sink) {
    int maxFlow = 0;
    int minCostMaxFlow = 0;
    while(BF(G, Source, Sink)) {
        int bottleNeck = oo;
        for(int i = Sink ; i != Source ; i = Father[i])
            bottleNeck = min(bottleNeck, C[Father[i]][i] - F[Father[i]][i]);
        if(!bottleNeck)
            break;
        for(int i = Sink ; i != Source ; i = Father[i]) {
            F[Father[i]][i] += bottleNeck;
            F[i][Father[i]] -= bottleNeck;
        }
        maxFlow += bottleNeck;
        minCostMaxFlow += bottleNeck * dp[Sink];
    }
    return minCostMaxFlow;
}

inline int getVar(int x) {
    if(mate[x] <= M)
        return mate[x];
    return getVar(mate[x] + N);
}

int main() {
    cin.sync_with_stdio(false);
    #ifndef ONLINE_JUDGE
    freopen(infile, "r", stdin);
    freopen(outfile, "w", stdout);
    #endif
    cin >> N >> M;
    for(int i = 1 ; i <= N ; ++ i) {
        cin >> A[i];
        nrBits[i] = bitCount(A[i]);
    }
    int Source = 0;
    int Sink = N + M + N + 1;
    for(int i = 1 ; i <= N + M ; ++ i) {
        G[Source].push_back(i);
        G[i].push_back(Source);
        cost[Source][i] = 0;
        C[Source][i] = 1;
    }
    for(int i = 1 ; i <= M ; ++ i) {
        for(int j = 1 ; j <= N ; ++ j) {
            G[i].push_back(j + N + M);
            G[j + N + M].push_back(i);
            cost[i][j + N + M] = nrBits[j];
            cost[j + N + M][i] = -nrBits[j];
            C[i][j + N + M] = 1;
        }
    }
    for(int i = 1 ; i <= N ; ++ i) {
        for(int j = i + 1 ; j <= N ; ++ j) {
            G[i + M].push_back(j + N + M);
            G[j + N + M].push_back(i + M);
            C[i + M][j + N + M] = 1;
            if(A[i] == A[j])
                continue;
            cost[i + M][j + N + M] = nrBits[j];
            cost[j + N + M][i + M] = -nrBits[j];
        }
    }
    for(int i = 1 ; i <= N ; ++ i) {
        G[i + N + M].push_back(Sink);
        G[Sink].push_back(i + N + M);
        C[i + N + M][Sink] = 1;
    }
    int minCostMaxFlow = getMinCostMaxFlow(G, Source, Sink);
    for(int i = 1 ; i <= N + M ; ++ i) {
        for(int j = 1 ; j <= N ; ++ j)
            if(F[i][j + N + M]) {
                mate[j + N + M] = i;
                match[i] = j + N + M;
            }
    }
    vector <pair<int, int> > Ans;
    for(int i = 1 ; i <= N ; ++ i) {
        int act = i + N + M;
        int var = getVar(act);
        Ans.push_back(make_pair(var, act));
    }
    int nr = Ans.size() + N;
    for(int i = 0 ; i < Ans.size() ; ++ i) {
        if(val[Ans[i].first] != A[Ans[i].second - N - M])
            ;
        else -- nr;
        val[Ans[i].first] = A[Ans[i].second - N - M];
    }
    memset(val, 0, sizeof(val));
    cout << nr << ' ' << minCostMaxFlow << '\n';
    for(int i = 0 ; i < Ans.size() ; ++ i) {
        if(val[Ans[i].first] != A[Ans[i].second - N - M]) {
            cout << char(Ans[i].first + 'a' - 1) << "=" << A[Ans[i].second - N - M] << "\n";
        }
        val[Ans[i].first] = A[Ans[i].second - N - M];
        cout << "print(" << char(Ans[i].first + 'a' - 1) << ")\n";
    }
    return 0;
}
